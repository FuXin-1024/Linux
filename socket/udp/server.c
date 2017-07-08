/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Sat 08 Jul 2017 07:44:25 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void Usage(const char* name)
{
	printf("Usage is %s [IP] [port]\n",name);
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}

	//创建套接字 套接字传输类型为数据报传输 SOCK_DGRM
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 2;
	}
	//绑定ip与端口
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		return 3;
	}
	//绑定后不需要设置为监听状态，因为udp是不可靠传输，不需要建立连接
	char buf[1024];
	while(1)
	{
		//udp客户端 - 服务器之间的通信采用的是 专门的函数通信
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		//recvfrom从客户端接受数据
		ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct ockaddr*)&client,&len);
		if(s < 0)
		{
			perror("recvfrom");
			return 4;
		}
		else if(s == 0)
		{}
		else
		{
			buf[s] = 0;
			printf("%s,%d #: %s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
			//调用sendto发送数据到客户端
			sendto(sock,buf,strlen(buf),0,(struct sockadd*)&client,len);
		}
	}
	close(sock);
	return 0;
}
