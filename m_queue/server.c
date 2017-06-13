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
		int size = recvMessage(msgid,CLIENT_TYPE,buf);
	//	printf("DEBUG: %d\n",size);
		if(size>0)
		{
			buf[size]='\0';
			printf("client say: %s",buf);
		//	printf("Debug: %s\n",buf);
		}
		else
		{
			break;
		}
		
		int ret = sendMessage(msgid,SERVER_TYPE,buf);
		if(ret<0)
			break;

	}
	destroyMsgQueue(msgid);
	return 0;
}
