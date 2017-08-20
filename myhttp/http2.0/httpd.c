/*************************************************************************
	> File Name: httpd.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 18 Aug 2017 07:50:06 AM PDT
 ************************************************************************/

#include"httpd.h"

void print_log(const char* str,int error)
{
	char* err[2] = {"WARNING","FATAL"};
	openlog("print_log",LOG_CONS|LOG_PID,LOG_USER);

	syslog(LOG_INFO,"%s%s\n",str,err[error]);
	closelog();
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


void clear_header(int sock)
{
	char buf[1024];
	int ret = 0;
	do
	{
		ret = get_line(sock,buf,sizeof(buf));
	}while(ret != 1 && strcmp("\n",buf));
}

int echo_www(int sock,const char* path,int size)
{
	printf("This os echo_www!\n");
	int outfd = open(path,O_RDONLY);
	if(outfd < 0)
	{
		print_log("open file(get outfd) error -- ",FATAL);
		return -1;
	}

	char buf[200] = "HTTP/1.0 200 OK\r\n\r\n<html><html>";
	int headret = send(sock,buf,sizeof(buf),0);
	if(headret <= 0)
	{
		print_log("ECHO head is error -- ",FATAL);
		return -1;
	}

	int ret = 0;
	if((ret = sendfile(sock,outfd,0,size)) < 0)
	{
		print_log("ECHO (CGI=0) is error --  ",FATAL);
		return -1;
	}

	return ret;
}

void Dealwithsock(int sock)
{
	char buf[SIZE];
	char method[100];
	char url[1024];
	char path[512];
	char Deal[100];
	char* query_string = NULL;
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
		while(url[j] != '?' && j < sizeof(path)-1)
		{
			path[j] = url[j];
			j++;
		}
		path[j] = '\0';
		if(url[j] == '?')
		{
			cgi = 1;
			query_string = url + j + 1;
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

		char All_path[512] = {0};
		sprintf(All_path,"wwwroot%s",path);
		printf("All_path:  %s\n",All_path);

		if(All_path[strlen(All_path)-1] == '/')
		{
			printf(" '\\' exist...\n");
			strcat(All_path,"index.html");
			printf("Allpath is :%s\n",All_path);
		}

		struct stat st;
		if(stat(All_path,&st) < 0)
		{
			clear_header(sock);
			print_log("FILE is unknow -- ",FATAL);
			exit(4);
		}
		else
		{
			printf(" '\\' no exist..\n");
			if(st.st_mode & S_IFDIR)
			{
				printf("file is dir..\n");
				All_path[strlen(All_path)] = '/';
				strcat(All_path,"index.html");
				printf("AllPath:%s\n",All_path);
			}
		}

		printf("CGI: %d\n",cgi);
		if((st.st_mode & S_IXUSR) ||\
			(st.st_mode & S_IXGRP) || \
			(st.st_mode & S_IXOTH))
		{
			cgi = 1;
		}

		printf("CGI: %d\n",cgi);
		if(cgi == 1)
		{
			echo_cgi(sock,method,All_path,query_string);
		}
		else
		{
			printf("cgi   =   0\n");
			clear_header(sock);
			printf("cgi   =   0\n");

			int ret = echo_www(sock,All_path,st.st_size);
			if(ret < 0)
			{
				print_log("echo_www is error -- ",FATAL);
				exit(5);
			}
			close(sock);
		}
}

int echo_cgi(int sock,const char* method,const char* path,const char* query)
{
	char buf[1024] = {0};
	int len = 0;

	printf("This is echo_cgi()!!!\n");

	if(strcmp("GET",method) != 0)
	{
		//POST
		printf("POST\n");
		int ret = 0;
		do
		{
			ret = get_line(sock,buf,sizeof(buf));
			printf("%s\n",buf);
			if(strncmp("Connect-Length:",buf,15) == 0)
			{
				len = atoi(&(buf[16]));
			}
		}
		while(ret > 0 && *buf != '\n');
		printf("len is %d\n",len);
		if(len <= 0)
		{
			print_log("Content-Length is error --",FATAL);
			exit(-1);
		}
	}
	else
	{
		//GET
		printf("This is echo_cgi()-->GET!\n");
		clear_header(sock);
	}

	int input[2];
	int output[2];

	if(pipe(input) < 0 || pipe(output) < 0)
	{
		print_log("pipe create error -- ",FATAL);
		close(sock);
		exit(-1);
	}

	printf("pipe is successful\n");
	pid_t id = 0;
	id = fork();
	printf("!!!!! id = %d\n",id);
	if(id < 0)
	{
		print_log("fork child error -- ",FATAL);
		close(sock);
		exit(-1);
	}

	else if(id > 0)//parent
	{
		printf("This is parent!\n");
		close(input[0]);
		close(output[1]);

		if(strcasecmp("POST",method) == 0)
		{
			char ch = '\0';
			int i = 0;
			for(i = 0; i<len; i++)
			{
				recv(sock,&ch,1,0);
				write(input[1],&ch,1);
			}
		}
		char ch = '\0';
		while(read(output[0],&ch,1) > 0)
		{
			send(sock,&ch,1,0);
		}
		close(sock);
		close(input[1]);
		close(output[0]);

		waitpid(id,NULL,0);
	}
	else//child
	{
		printf("This is child,\n");
		close(input[1]);
		close(output[0]);

		dup2(input[0],0);
		dup2(output[1],1);

		char Method[255] = {0};
		char content_len[255] = {0};
		char query_string[255] = {0};

		sprintf(Method,"METHOD=%s",method);
		putenv(Method);
		if(!strcasecmp(method,"POST"))
		{
			sprintf(content_len,"CONTENT_LEN=%s",len);
			putenv(content_len);
		}

		if(!strcasecmp(method,"GET"))
		{
			sprintf(query_string,"QUERY_STRING=%s",query);
			putenv(query_string);
		}

		execl(path,path,NULL);
		printf("execl is error\n");
		exit(0);
	}
}
