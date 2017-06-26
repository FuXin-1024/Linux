/*************************************************************************
	> File Name: product.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 26 Jun 2017 09:12:55 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct _list
{
	struct _list *next;
	int _val;
}product_list;

product_list *head = NULL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t need_product = PTHREAD_COND_INITIALIZER;

void Init_list(product_list* list)
{
	if(list != NULL)
	{
		list -> next = NULL;
		list -> _val = 0;
	}
}

void* Consumer(void* _val)
{
	product_list *p = NULL;
	for(;;)
	{
		pthread_mutex_lock(&lock);
		while(head == NULL)
		{
			pthread_cond_wait(&need_product,&lock);
		}
		p = head;
		head = head -> next;
		p -> next = NULL;
		pthread_mutex_unlock(&lock);
		printf("Consum success,val is:%d\n",p -> _val);
		free(p);
	}
	return NULL;
}

void* Product(void* _val)
{
	for(;;)
	{
		sleep(rand() % 2);
		product_list* p =malloc(sizeof(product_list));
		pthread_mutex_lock(&lock);
		Init_list(p);
		p -> _val = rand() % 1000;
		p -> next = head;
		head = p;
		pthread_mutex_unlock(&lock);
		printf("Call consumer! Product has producted,val is:%d\n",p->_val);
		pthread_cond_signal(&need_product);
	}
}

int main()
{
	pthread_t t_product;
	pthread_t t_consumer;
	pthread_create(&t_product,NULL,Product,NULL);
	pthread_create(&t_consumer,NULL,Consumer,NULL);

	pthread_join(t_product,NULL);
	pthread_join(t_consumer,NULL);
	return 0;
}

