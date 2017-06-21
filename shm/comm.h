/*************************************************************************
	> File Name: comm.h
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 20 Jun 2017 11:56:28 AM PDT
 ************************************************************************/

#ifndef __COMM__
#define __COMM_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
#define PROJID 0x666
#define SIZE 4096

int commMem(int flags);
int creatMem();
int getMem();
int destroyMem(int shmid);

#endif
