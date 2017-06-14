/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 13 Jun 2017 11:37:30 AM PDT
 ************************************************************************/

#include"comm.h"

int main()
{
	int msgid = creatMsgQueue();
	char buf[MYSIZE*2];
	while(1)
	{
		 buf[0]=0;
		 recvMessage(msgid,CLIENT_TYPE,buf);
		 printf("client say: %s\n",buf);
		 printf("Please Enter# ");
		 fflush(stdout);
		 ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]=0;
			sendMessage(msgid,SERVER_TYPE,buf);
		}	
	}
	destroyMsgQueue(msgid);
	return 0;
}
