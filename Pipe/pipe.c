/*************************************************************************
	> File Name: pipe.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Fri 12 May 2017 08:53:50 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
//创建管道，子进程只写，父进程只读

int main()
{
	int fds[2];
	int ret=pipe(fds);
	if(ret==-1)
	{
		printf("Create pipe error! errno code  is:%d\n",errno);
		return 1;
	}

	pid_t id=fork();
	if(id<0)
	{
		printf("fork error!");
		return 2;
	}
	else if(id==0)
	{
		//child
		close(fds[0]);//关闭读
		char* msg="I am child!";
		while(1)
		{
			write(fds[1],msg,strlen(msg)+1);
			sleep(1);
		}
	}
	else
	{
		close(fds[1]);//关闭写
		char buf[1024];
		while(1)
		{
		read(fds[0],buf,sizeof(buf));
		printf("father read :%s\n",buf);
		}
	
	}
	return 0;
}
