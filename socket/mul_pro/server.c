/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Thu 06 Jul 2017 10:01:16 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void Usage(const char* name)
{
	printf("Usage:%s [IP] [port]\n",name);
}

int StartUp(int port, const char* ip)
{
	int ListenSock = socket(AF_INET,SOCK_STREAM,0);
	if(ListenSock < 0)
	{
		perror("socket");
		return 1;
	}
	int opt = 1;
	setsockopt(ListenSock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(ListenSock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		return 2;
	}
	if(listen(ListenSock,5) < 0)
	{
		perror("listen");
		return 3;
	}
	return ListenSock;
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}

	int len;
	int listenSock = StartUp(atoi(argv[2]),argv[1]);
	struct sockaddr_in client;
	while(1)
	{
		int sock = accept(listenSock,(struct sockaddr*)&client,&len);
		if(sock < 0)
		{
			perror("accept");
			continue;
		}

		printf("get a client is %s,port is %d\n",inet_ntoa(client.sin_addr),\
				ntohs(client.sin_port));
		int id = fork();
		if(id > 0)
		{
			close(sock);
			while(waitpid(-1,NULL,WNOHANG) > 0);
			continue;
		}
		else
		{
			close(listenSock);
			if(fork() > 0)
			{
				exit(0);
			}
			char buf[1024];
			while(1)
			{
				ssize_t s = read(sock,buf,sizeof(buf)-1);  //服务器进行读数据
				if(s > 0)
				{
					buf[s] = 0;
					printf("client# %s\n",buf);
				}
				else
				{
					//数据已经读完了，客户端不发送数据了
					printf("client is quit!\n");
					break;
				}
			}
			close(sock);
			break;
		}
	}
	return 0;
}


