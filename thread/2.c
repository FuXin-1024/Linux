/*************************************************************************
	> File Name: 2.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 30 Jun 2017 09:02:26 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define _SIZE_ 5
sem_t blanks; //表示格子的信号量
sem_t datas;  //表示商品的信号量
int buf[_SIZE_] ={ 0 };

//生产者
void* product(void* arg)
{
	int i = 0;
	while(1)
	{

		sem_wait(&blanks); //生产者申请格子资源
		int data = rand()%1000;
		buf[i] = data;
		printf("Product is:%d\n",data);
		usleep(500000);
		sem_post(&datas); //每生产一个商品就需要对商品信号量+1
	
		++i;
		i %= _SIZE_;
	}
}

//消费者
void* consumer(void* arg)
{
	int i = 0;
	while(1)
	{

	    sem_wait(&datas);  //消费者申请商品资源
		printf("Consumer %d\n",buf[i]);
	//	usleep(500000);
	    sleep(5);
		sem_post(&blanks); //买走一个商品，就多了一个空格子

		++i;
		i %= _SIZE_;
	}
}

int main()
{
	sem_init(&blanks,0,_SIZE_);
	sem_init(&datas,0,0);
	pthread_t _consumer;
	pthread_t _product;
	pthread_create(&_consumer,NULL,consumer,NULL);
	pthread_create(&_product,NULL,product,NULL);
	pthread_join(_consumer,NULL);
	pthread_join(_product,NULL);
	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;
}
