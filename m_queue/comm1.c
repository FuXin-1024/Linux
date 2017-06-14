/*************************************************************************
	> File Name: comm.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 13 Jun 2017 11:10:33 AM PDT
 ************************************************************************/

#include"comm.h"

int commMsgQueue(int flag)
{
	key_t _k=ftok(PATHNAME,PROJID);
	if(_k<0)
	{
		perror("ftok");
		return -1;
	}
	int msg_id=msgget(_k,flag);
	if(msg_id<0)
	{
		perror("msgget");
		return -2;
	}
	return msg_id;
}

int creatMsgQueue()
{
	return commMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}

int getMsgQueue()
{
	return commMsgQueue(IPC_CREAT);
}

int sendMessage(int msg_id,long type,const char* msg)
{
	struct msgbuf buf;
	buf.mtype=type;
	strcpy(buf.mtext,msg);

	int ret=msgsnd(msg_id,&buf,sizeof(buf.mtext),0);
	if(ret<0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}

int recvMessage(int msg_id,long type,char out[])
{
	struct msgbuf buf;
	int size=msgrcv(msg_id,&buf,sizeof(buf.mtext),type,0);
	if(size>0);
	{
	//	printf("%d",size);
		buf.mtext[size-1]='\0';
	//	printf("Debug 0:%s\n",buf.mtext);
		strncpy(out,buf.mtext,sizeof(buf.mtext));
		return size;
	}
	perror("msgrcv");
	return -1;
}

int destroyMsgQueue(int msg_id)
{

	if(msgctl(msg_id,IPC_RMID,NULL) < 0)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
