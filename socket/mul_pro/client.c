/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 07 Jul 2017 07:47:04 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void Usage(const char* name)
{
	printf("Usage:%s [IP] [port]",name);
}
int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
	{
		perror("connec");
		return 3;
	}
	char buf[1024];
	while(1)
	{
		printf("send# ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s < 0)
		{
			perror("read");
			break;
		}
		buf[s-1] = 0;
		write(sock,buf,s);
	}
	close(sock);
	return 0;
}

