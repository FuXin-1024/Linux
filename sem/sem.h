/*************************************************************************
	> File Name: sem.h
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Wed 14 Jun 2017 12:37:39 PM PDT
 ************************************************************************/

#ifndef _SEM_H_
#define _SEM_H_

#define PATHNAME "."
#define PROJ_ID 0x6666
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

union semun
{
	int val;                   //使用的值
	struct semid_ds *buf;      //IPC_STAT、IPC_SET  使用缓存
	unsigned short *array;     //AETALL、SETALL     使用的数组
	struct seminfo *__buf;	   //IPC_INFO(Linux特有)使用缓存区
};

int CreateSem(int nums);
int DestroySem(int semid);
int GetSem(int nums);
int InitSem(int semid,int which);
int P(int semid,int which);
int V(int semid,int which);

#endif
