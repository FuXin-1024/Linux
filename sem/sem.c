/*************************************************************************
	> File Name: sem.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Wed 14 Jun 2017 12:53:07 PM PDT
 ************************************************************************/

#include"sem.h"

int ComSem(int nums,int flag)
{
	key_t key=ftok(PATHNAME,PROJ_ID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int semid=semget(key,nums,flag|0666);
	if(semid<0)
	{
		perror("semget");
		return -2;
	}
	return semid;
}

static int op_sem(int semid,int op,int which)
{
	struct sembuf sem;
	sem.sem_num=which;
	sem.sem_op=op;
	return semop(semid,&sem,1);
}

int P(int semid,int which)
{
	int ret=op_sem(semid,-1,which);
	if(ret==0)
		return 0;
	else
		return -1;
}

int V(int semid,int which)
{
	int ret=op(semid,1,which);
	
	if(ret==0)
		return 0;
	else
		return -1;
}

int CreateSem(int nums)
{
	return ComSem(nums,IPC_CREAT|IPCEXCL);
}

int GetSem(int nums)
{
	return ComSem(nums,IPC_CREAT);
}

int DestroySem(int semid)
{
	if(semctl(semid,0,IPC_RMID)<0)
	{
		perror("semctl");
		return -1;
	}
}

int InitSem(int semid,int which)
{
	union semun sem;
	sem.val=1;
	int ret=semctl(semid,which,SETVAL,sem);
	if(ret<0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}


