/*************************************************************************
	> File Name: main.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Wed 14 Jun 2017 01:16:41 PM PDT
 ************************************************************************/

#include"sem.h"

int main()
{
	int semid=CreateSem(12);
	if(semid<0)
	{
		perror("semid");
		return -1;
	}
	InitSem(semid,1);
	sleep(5);
	//DestroySem(semid);
	pid_t id=fork();
	if(id==0)
	{
		//child
		while(1)
		{
			P(semid,1);
			printf("A");
			fflush(stdout);
			usleep(100000);
			printf("A ");
			fflush(stdout);
			usleep(100000);
			V(semid,1);
		}
	}
	else
	{
		//father
		while(1)
		{
			P(semid,1);
			printf("B");
			fflush(stdout);
			usleep(100000);
			printf("B ");
			fflush(stdout);
			usleep(100000);
			V(semid,1);
		}
	}
	wait(NULL);
	return 0;
}
