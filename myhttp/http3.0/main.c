/*************************************************************************
	> File Name: main.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 18 Aug 2017 08:33:37 PM PDT
 ************************************************************************/

#include"httpd.h"

void* thread_mechine(void* arg)
{
	int sock = (int)arg;
	if(pthread_detach(pthread_self()) != 0)
	{
		print_log("pthread_detach error -- ",FATAL,__LINE__);
		close(sock);
		return NULL;
	}

	printf("11\n");
	Dealwithsock(sock);
	return NULL;
}

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("Please input: %s[IP] [PORT] \n",argv[0]);
		exit(1);
	}

	int listensock = startup(argv[1],argv[2]);
	if(listensock < 0)
	{
		print_log("startup error -- ",FATAL,__LINE__);
		exit(2);
	}
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	while(1)
	{
		sleep(1);
		printf("...\n");
		int sock = accept(listensock,(struct sockaddr*)&addr,&len);
		if(sock < 0)
		{
			print_log("accept error -- ",WARNING,__LINE__);
			continue;
		}

		printf("haha\n");
		pthread_t tid;
		if(pthread_create(&tid,NULL,thread_mechine,(void*)sock) < 0)
		{
			print_log("pthread_create error -- ",FATAL,__LINE__);
			close(sock);
			continue;
		}
	}
	return 0;
}
