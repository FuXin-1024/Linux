/*************************************************************************
	> File Name: pthread4.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 16 Jun 2017 01:56:43 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

//新线程，每秒打印一次，打印五次
void* thread_run(void *arg)
{

	pthread_detach(pthread_self());
	printf("%s\n",(char*)arg);
	return NULL;
}

int main()
{
	//主线程
	printf("pthread\n");
	pthread_t tid;
	int ret=pthread_create(&tid,NULL,thread_run,"thread is running!!");
	if(ret != 0)
	{
		printf("pthread_creat error\n");
		return -1;
	}

	//wait
	int ret1=0;
	sleep(1);
	if(0== pthread_join(tid,NULL))
	{
		printf("pthread wait success!\n");
		ret1 = 0;
	}
	else
	{
		printf("pthread wait failed!\n");
		ret1 = 1;
	}
	return ret1;
}
