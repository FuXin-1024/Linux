/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 20 Jun 2017 12:13:59 PM PDT
 ************************************************************************/

#include"comm.h"

int main()
{
	printf("client\n");
	int shmid = getMem();
	if(shmid < 0)
	{
		printf("getMem error!");
		return -1;
	}
	printf("shmid: %d\n",shmid);
	sleep(5);
	char *addr=shmat(shmid,NULL,0);
	if(addr == NULL)
	{
		printf("addr is NULL!\n");
	}
	printf("Debug add %p\n",addr);

	if(addr < 0)
	{
		perror("client shmat");
		return -1;
	}

	int i = 0;
	while(i < SIZE-1)
	{
		addr[i] ='a' ;
		addr[i+1] = '\0';
		sleep(1);
		i++;
	}

	int ret=shmdt(addr);
	printf("Debug shmdt\n");
	if(ret < 0)
	{
		perror("client shmdt");
		return -1;
	}
	return 0;
}

