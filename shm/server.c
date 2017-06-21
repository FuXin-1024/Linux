/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 20 Jun 2017 12:23:49 PM PDT
 ************************************************************************/

#include "comm.h"

int main()
{
	printf("server\n");
	int shmid = creatMem();
	sleep(10);
	if(shmid < 0)
	{
		printf("creatMem error!\n");
		return -1;
	}

	char *addr=shmat(shmid,NULL,0);
	if(addr < 0)
	{
		perror("shmat");
		return -2;
	}
	while(1)
	{
		printf("# ");
		printf("%s",addr);
		printf(" #\n");
		sleep(1);
	}

	int ret = shmdt(addr);
	if(ret < 0)
	{
		perror("shmdt");
		return -1;
	}
/*
	int ret_des=destroyMem(shmid);
	if(ret_des < 0)
	{
		printf("destroyMem error!\n");
		return -1;
	}
*/
	return 0;
}
