/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Wed 05 Jul 2017 08:37:30 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>


void Usage(const char* name)
{
	printf("Usage:%s [IpAddress] [port]\n",name);
}

int StartUp(int port, const char* ip)
{
	int ListenSock = socket(AF_INET,SOCK_STREAM,0);	
	if(ListenSock < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(ListenSock,(struct sockaddr*)&local,sizeof(local)) < 0)
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
		int sock = accept(listenSock,(struct sockaddr*)&client,&len);//获取客户机的信息
		if(sock < 0)
		{
			perror("accept");
			continue;
		}
		printf("Get a client,IP is %s,port is %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		char buf[1024];
		while(1)
		{
			ssize_t s = read(sock,buf,sizeof(buf)-1);//从服务器读数据
			 if(s == 0)
			{
				//数据已经读完了，客户端不发送数据了
				printf("client is quit!\n");
				return 2;
			}
			 else if(s <0)
			{
				perror("read");
				return 3;
			}
			 else
			{
				buf[s] = 0;
				printf("client# %s\n",buf);
			//	write(sock, buf, strlen(buf));
			
	        	printf("say: ");
	        	fflush(stdout);
				ssize_t _s = read(0,buf,sizeof(buf)-1);
	        	if(_s <= 0)
	        	{
	        		perror("read");
	        		return 1;
	        	}
	        	buf[_s-1]=0;
	        	write(sock,buf,sizeof(buf)-1);
			}
		}
	close(sock);
	}
	
	return 0;
}
