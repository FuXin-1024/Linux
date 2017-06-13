/*************************************************************************
	> File Name: comm.h
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 13 Jun 2017 10:57:17 AM PDT
 ************************************************************************/

#ifndef _COMM_
#define _COMM_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define MYSIZE 128

#define PATHNAME "."
#define PROJID 0x6666

#define CLIENT_TYPE 1
#define SERVER_TYPE 2

struct msgbuf
{
	long mtype;
	char mtext[MYSIZE];
};

int commMsgQueue(int flag);
int creatMsgQueue();
int getMsgQueue();
int sendMessage(int msgid.long type,const char *buf);
int destroyMsgQueue(int msgid);

#endif


