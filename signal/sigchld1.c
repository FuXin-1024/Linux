/*************************************************************************
	> File Name: sigchld1.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Mon 10 Jul 2017 08:14:18 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

//父进程等待子进程的异步方式
 void handler(int sig)
{
	printf("father is catching,child is quit!\n");
	
	//以阻塞方式等待所有异常退出的子进程
	pid_t id;
	while((id = waitpid(-1,NULL,WNOHANG)) > 0)
	{
		printf("wait child success: %d\n",id);
	}
}

int main()
{
	signal(SIGCHLD,handler);
	pid_t id = fork();
	if(id == 0)
	{
		//child
		printf("I a child,quit! pid: %d\n",getpid());
		exit(1);
	}
	else
	{
		//father
		while(1)
		{
			printf("father is doing something!\n");
			sleep(1);
		}
	}
	return 0;
}
