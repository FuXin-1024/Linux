/*************************************************************************
	> File Name: count.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 26 Jun 2017 07:58:07 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

static int g_count = 0;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
void* read_write_num(void* _val)
{
	int val = 0;
	int i = 0;
	for(; i<5000; ++i)
	{
		pthread_mutex_lock(&mutex_lock);
		val  = g_count;
		printf("pthread id is:%x,count is : %d\n",(unsigned long)pthread_self(),g_count);
		g_count = val + 1;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,read_write_num,NULL);
	pthread_create(&tid2,NULL,read_write_num,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("count final val is:%d\n ",g_count);
	return 0;
}
