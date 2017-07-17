/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 17 Jul 2017 08:55:03 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void Usage(const char* name)
{
	printf("Usage:%s [IP] [port]\n");
}

int main(int argc,char* argv[])
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

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("connecct");
		return 3;
	}
	printf("connect success\n");

	char buf[1024];
	while(1)
	{
		printf("client # ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s <= 0)
		{
			perror("read");
			return 4;
		}
		else
		{
			buf[s-1] = 0;
			int fd = dup(1);
			dup2(sock,1);
			printf("%s",buf);
			fflush(stdout);
			dup2(fd,1);
		}
		s = read(sock,buf,sizeof(buf)-1);
		if(s == 0)
		{
			printf("server quit\n");
			break;
		}
		else if(s < 0)
		{
			perror("read");
			return 5;
		}
		else
		{
			buf[s] = 0;
			
			printf("server #%s\n",buf);
		}
	}
	close(sock);
	return 0;
}

