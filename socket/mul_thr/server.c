/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 07 Jul 2017 08:31:39 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>

void Usage(const char* name)
{
	printf("Usage is %s [IP] [port]\n",name);
}

int StartUp(int port,const char* ip)
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
	if(bind(ListenSock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		return 2;
	}
	if(listen(ListenSock,5) < 0)
	{
		perror(("listen"));
		return 3;
	}
	return ListenSock;
}

void* thread_hander(void* arg)
{
	int sock = *((int*)arg);
	char buf[1024];
	while(1)
	{
		ssize_t _s  = read(sock,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s-1]=0;
			printf("client say# %s\n",buf);
			if(write(sock,buf,sizeof(buf)-1) < 0)
			{
				break;
			}
		}
		else if(_s == 0)
		{
			printf("client is quit!\n");
			break;
		}
		else
		{
			perror("read");
			break;
		}
	}
	close(sock);
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}
	int listenSock = StartUp(atoi(argv[2]),argv[1]);
	struct sockaddr_in client;
	int len = 0;
	while(1)
	{
		int sock = accept(listenSock,(struct sockaddr*)&client,&len);
		if(sock < 0)
		{
			perror("accept");
			continue;
		}
		printf("Get a client! IP is %d\n,port is %d\n",inet_ntoa(client.sin_addr),\
				ntohs(client.sin_port));
		pthread_t tid;
		int ret = pthread_create(&tid,NULL,thread_hander,&sock);
		if(ret < 0)
		{
			perror("pthread_create");
			return 3;
		}
		pthread_detach(tid);
	}
	return 0;
}
