/*************************************************************************
	> File Name: comm.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 20 Jun 2017 12:06:38 PM PDT
 ************************************************************************/

#include"comm.h"

int commMem(int flags)
{
	key_t _k=ftok(PATHNAME,PROJID);
	if(_k<0)
	{
		perror("ftok");
		return -1;
	}

	int shmid = shmget(_k,SIZE,flags);
	if(shmid<0)
	{
		perror("shmget");
		return -2;
	}
	return shmid;
}

int creatMem()
{
	return commMem(IPC_CREAT | IPC_EXCL | 0666);
}

int getMem()
{
	return commMem(IPC_CREAT);
}

int destroyMem(int shmid)
{
	int ret = shmctl(shmid,IPC_RMID,NULL);
	if(ret<0)
	{
		perror("destroy shmctl");
		return -1;
	}
	return 0;
}
