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
	char out[MYSIZE*2];

	while(1)
	{
		printf("Please Enter # ");
		fflush(stout);
		int ret = read(0,buf,MYSIZE-1);
		if(ret>0)
		{
			buf[ret]='\0';
			printf("Debug client: %s\n",buf);
			sendMessage(msgid,CLIENT_TTYPE,buf);
		}
		if(recvMessage(msgid,CLIENT_TYPE,out)<0)
		{
			break;
		}
		printf("server echo # %s\n ",out);
	}
	return 0;
}
