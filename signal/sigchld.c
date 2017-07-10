/*************************************************************************
	> File Name: sigchld.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 10 Jul 2017 08:06:09 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

//子进程退出时，会给父进程发送SIGCHLD信号
void handler(int sig)
{
	printf("Get a sig: %d,pid: %d\n",sig,getpid());
}

int main()
{
	signal(SIGCHLD,handler);
	pid_t id = fork();
	if(id == 0)
	{
		//child
		printf("I am a child,quit! pid %d\n",getpid());
		exit(1);
	}
	else
	{
		//father
		waitpid(id,NULL,0);  // 以阻塞方式等待
	}
	return 0;
}
