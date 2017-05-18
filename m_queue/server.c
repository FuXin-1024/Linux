/*************************************************************************
	> File Name: server.c
	> Author: fx
	> Mail: 1007160080@qq.com 
	> Created Time: Thu 18 May 2017 01:59:43 PM PDT
 ************************************************************************/
//发送端
#include"comm.h"

int main()
{
	int msgid=creatMsgQueue();
	char buf[MSG_SIZE*2];

	while(1)
	{
		int size = recvMessage(msgid,CLIENT_TYPE,buf);
		 printf("DEBUG: %d\n",size);
		 if(size > 0)
		 {
			 buf[size] = '\0';
			 printf("client say: %s\n",buf);
			 printf("Debug : %s\n",buf);
		 }
		 else
		 {
			 break;
		 }
	     int ret = sendMessage(msgid,SERVER_TYPE,buf);
		 if(ret < 0)
		 {
			 break;
		 }
	}
	destroyMsgQueue(msgid);
	return 0;
}
