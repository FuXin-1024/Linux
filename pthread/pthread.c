/*************************************************************************
	> File Name: pthread.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 16 Jun 2017 01:11:39 PM PDT
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
		printf("thread,pid:%d ,ppid:%d ,tid:%d %1u\n",getpid(),getppid().pthread_self());
	}
	printf("thread is over...\n");
	return NULL;
}

