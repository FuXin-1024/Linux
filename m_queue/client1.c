/*************************************************************************
	> File Name: client.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 13 Jun 2017 11:29:38 AM PDT
 ************************************************************************/

#include"comm.h"

int main()
{
	int msgid=getMsgQueue();
	char buf[MYSIZE];

	while(1)
	{
		buf[0]=0;
		printf("Please Enter#");
		fflush(stdout);
		ssize_t  ret = read(0,buf,sizeof(buf)-1);
		if(ret>0)
		{
			buf[ret-1]=0;
			sendMessage(msgid,CLIENT_TYPE,buf);
		}
		recvMessage(msgid,SERVER_TYPE,buf);
	
		printf("server say # %s\n",buf);
	}
	return 0;
}
