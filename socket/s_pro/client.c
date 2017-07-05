/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Wed 05 Jul 2017 09:20:38 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


void Usage(const char* name)
{
	printf("Usage:%s [IpAddress] [port]\n",name);
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
		perror("socke");
		return 2;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
	{
		perror("connect");
		return 3;
	}

	//printf("connect success!\n");
	char buf[1024];
	while(1)
	{
		printf("send# ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s <= 0)
		{
			perror("read");
			return 4;
		}
		buf[s-1] = 0;
		write(sock,buf,strlen(buf));

		ssize_t _s = read(sock, buf, sizeof(buf)-1);
		if(_s == 0)
		{
			printf("server quit\n");
			break;
		}
		else if(_s < 0)
		{
			perror("read");
			return 5;
		}
		else
		{
			buf[s]=0;
			printf("server #: %s\n", buf);
		}
	}
	close(sock);
	return 0;
}

