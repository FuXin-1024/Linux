/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 17 Jul 2017 07:35:40 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<unistd.h>
#include<string.h>

#define SIZE sizeof(fd_set)*8

int readfds[SIZE];  //保存所有文件描述符的数组

void Usage(const char* name)
{
	printf("Usage:%s [IP] [port]\n",name);
}

int StartUp(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		return 2;
	}

	if(listen(sock,5) < 0)
	{
		perror("listen");
		return 3;
	}
	return sock;
}

int main(int argc,char* argv[])
{

	//printf("hello\n");
	if(argc != 3)
	{
		Usage(argv[0]);
		return 4;
	}

	int sock = StartUp(argv[1],atoi(argv[2]));

	int i = 0;
	for(; i<SIZE; ++i)
	{
		readfds[i] = -1;//全部初始化为-1
	}
	readfds[0] = sock;
	int max_fd = readfds[0]; //保存最大的文件描述符做select函数的参数

	while(1)
	{
		fd_set rfds,wfds;
		char buf[1024];
		FD_ZERO(&rfds); //将文件描述符集指针指向的文件描述符集清零
		int j = 0;
		for(; j<SIZE; ++j)
		{
			if(readfds[j] != -1)
				FD_SET(readfds[j],&rfds);//将文件描述符设置进文件描述符集指针指向的文件描述符集中
			if(max_fd < readfds[j])
				max_fd = readfds[j];
		}
	
		struct timeval timeout = {5,0};
		switch (select(max_fd+1,&rfds,&wfds,NULL,&timeout))
		{
			case -1:
				{
					perror("select");
					break;
				}
			case 0:
				{
					printf("timeout...\n");
					break;
				}
			default:
				
				{
					int k = 0;
					for(; k<SIZE; ++k)
					{
						if(readfds[k] == sock && FD_ISSET(readfds[k],&rfds))
						{
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							int newsock = accept(sock,(struct sockaddr*)&peer,&len);
							if(newsock < 0)
							{
								perror("accept");
								continue;
							}

							int l = 0;
							for(; l<SIZE; ++l)
							{
								if(readfds[l] == -1)
								{
									readfds[l] = newsock;
									break;
								}
							}
							if( l == SIZE)
							{
								printf("readfds is full\n");
								return 5;
							}
						}
						else if(readfds[k] > 0 && FD_ISSET(readfds[k],&rfds))
						{
							ssize_t s = read(readfds[k],buf,sizeof(buf)-1);
							if(s < 0)
							{
								perror("read");
								return 6;
							}
							else if(s == 0)
							{
								printf("client quit\n");
								readfds[k] = -1;
								close(readfds[k]);
								continue;
							}
							else
							{
								buf[s] = 0;
								printf("client # %s\n",buf);
								fflush(stdout);
								write(readfds[k],buf,strlen(buf));
							}
						}
					}
				}
				break;
		}

	}
	close(sock);
	return 0;
}
