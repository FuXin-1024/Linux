/*************************************************************************
	> File Name: comm.h
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Tue 16 May 2017 01:34:07 PM PDT
 ************************************************************************/

#ifndef __COMM__
#define __COMM__

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define MSG_SIZE 1024
#define PATHNAME "."
#define PROJID 0x6666

#define CLIENT_TYPE 1
#define SERVER_TYPE 2


 strut _msgbuf
{
	long mtype;
	char mtext[MSG_SIZE];
}msginfo;

int commMsgQueue(int flag);
int creatMasQueue();
int getMsgQueue();
int sendMessage(int msgid,long type,const char* buf);
inr recvMessage(int msgid,long type,char* buf);
int destroyMsgQueue(int msgid);

#endif;
