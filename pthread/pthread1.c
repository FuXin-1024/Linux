/*************************************************************************
	> File Name: pthread1.c
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
	int count=0;
	while(count++<5)
	{
		sleep(1);
		printf("thread,pid:%d ,ppid:%d ,tid:%d %1u\n",getpid(),getppid(),pthread_self());
	}
	printf("thread is over...\n");
	return NULL;
}

int main()
{
	//主线程
	printf("pthread\n");
	pthread_t tid;
	int ret=pthread_create(&tid,NULL,thread_run,pthread_self());
	if(ret != 0)
	{
		printf("pthread_creat error\n");
		return -1;
	}
	else
	{
		sleep(1);
		printf("main,pid:%d ,ppid:%d ,tid:%d %1u\n",getpid(),getppid(),pthread_self());
	}

	pthread_cancel(tid);//在主线程结束子线程

	int exitCode;
	pthread_join(tid,(void**)&exitCode);
	printf("main is over..%d\n",exitCode);
	return 0;
}
