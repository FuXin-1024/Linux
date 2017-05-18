/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080@qq.com 
	> Created Time: Thu 18 May 2017 01:45:44 PM PDT
 ************************************************************************/

#include<stdio.h>
#include "comm.h"
//接收端
int main()
{
	int msgid=getMsgQueue();
	char buf[MSG_SIZE];
	char out[MSG_SIZE*2];

	while(1)
	{
		printf("Please Enter #");
		fflush(stdout);
		int ret=read(0,buf,Msg_SIZE-1);

		if(ret>0)
		{
			buf[ret]='\0';
			printf("Debug client :%s\n",buf);
			sendMessage(msgid,CLIENT_TYPE,buf);
		}

		if(recvMessage(msgid,SERVER_TYPE,out)<0)
			break;
		printf("server echo # %s\n",out);
	}
	return 0;
}
