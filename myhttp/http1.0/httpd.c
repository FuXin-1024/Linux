/*************************************************************************
	> File Name: httpd.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 18 Aug 2017 07:50:06 AM PDT
 ************************************************************************/

#include"httpd.h"

void print_log(const char* str,int error)
{
	printf("%s%d\n",str,error);
}

int startup(const char* ip,const char* port)
{
	assert(ip);
	assert(port);

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		print_log("socket error -- ",FATAL);
		exit(1);
	}

	int opt = 1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0)
	{
		printf("setsockopt error -- ",WARNING);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = inet_addr(ip);

	int len = sizeof(addr);
	if(bind(sock,(struct sockaddr*)&addr,len) < 0)
	{
		print_log("bind error -- ",FATAL);
		close(sock);
		exit(2);
	}

	if(listen(sock,5) < 0)
	{
		print_log("listen error -- ",FATAL);
		close(sock);
		exit(3);
	}

	return sock;
}

int get_line(int sock,char* buf,int size)
{
	int i = 0;
	char c = '\0';
	int n;

	//将终止条件统一为 \n 换行符，标准化buf数组
	while((i < size-1) && (c != '\n'))
	{
		//一次接受一个字节
		n = recv(sock,&c,1,0);
		if( n > 0)
		{
			//收到 \r 则继续接收下一个字符，因为换行符可能是 \r\n
			if(c == '\r')
			{
				//使用MSG_PEEK标志使下一次读取依然可以得到这次读取的内容
				n = recv(sock,&c,1,MSG_PEEK);
				if((n > 0) && (c == '\n'))
					recv(sock,&c,1,0);
				else
					c = '\n';
			}
			//存到缓冲区
			buf[i] = c;
			i++;
		}
		else
			c = '\n';
	}
	buf[i] = '\0';
	return i;
}

void Dealwithsock(int sock)
{
	char buf[SIZE];
	char method[100];
	char url[1024];
	char path[512];
	char Deal[100];

	int cgi = 0;

	int s = get_line(sock,buf,sizeof(buf));
	int i = 0;
	int j = 0;

	printf("%s\n",buf);

	while(!isspace(buf[i]) && i < (sizeof(method)-1))
	{
		method[i] = buf[i];
		i++;
	}

	method[i]='\0';

	while(isspace(buf[i]) && i<sizeof(buf))
		i++;

	while(!isspace(buf[i]) && j < (sizeof(url)-1))
	{
		url[j] = buf[i];
		i++;
		j++;
	}

	if(strcasecmp("GET",method) && strcasecmp("POST",method))
	{
		print_log("Method is error -- ",FATAL);
		close(sock);
		exit(3);
	}

	if(!strcasecmp("POST",method))
	{
		cgi = 1;
	}

	if(!strcasecmp("GET",method))
	{
		j = 0;
		while(url[i] != '?' && j < sizeof(path)-1)
		{
			path[j] = url[j];
			j++;
		}
		path[j] = '\0';
		if(url[j] == '?')
		{
			cgi = 1;
		}
	}
		while(isspace(buf[i]) && i < sizeof(buf))
		{
			i++;
		}

		int k = 0;
		while(!isspace(buf[i]) && k < sizeof(Deal)-1)
		{
			Deal[k] = buf[i];
			k++;
			i++;
		}

		printf("CGI: %d\n",cgi);
		printf("Method: %s\n",method);
		printf("path: %s\n",path);
		printf("url: %s\n",url);
		printf("Deal: %s\n",Deal);
}
