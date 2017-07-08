/*************************************************************************
	> File Name: client.c
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
	//创建成功
	char buf[1024];
	printf("Please Enter\n");
	while(1)
	{
		printf("client#: ");
		fflush(stdout);
		//从标准输入中读数据
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s < 0)
		{
			perror("read");
			return 3;
		}
		buf[s-1] = 0;
		//给定接受方的协议地址
		struct sockaddr_in peer;
		peer.sin_family = AF_INET;
		peer.sin_port = htons(atoi(argv[2]));
		peer.sin_addr.s_addr = inet_addr(argv[1]);
		//向服务器发送数据
		if(sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,sizeof(peer)) < 0)
		{
			perror("sendto");
			return 4;
		}
		struct sockaddr_in server;
		socklen_t len = sizeof(server);
		//接受服务器的数据
		s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
		if(s < 0)//接受失败
		{
			perror("recvfrom");
			return 5;
		}
		else if(s == 0) //接受到文件结尾，表示服务器关闭
		{
			printf("server quit!\n");
			break;	
		}
		else //接受到的数据放到显示器上
		{
			buf[s] = 0;
			printf("%s ,%d #：%s\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),buf);
		}
	}
	close(sock);
	return 0;
}
