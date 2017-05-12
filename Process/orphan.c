/*************************************************************************
	> File Name: orphan.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Fri 12 May 2017 12:44:27 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

//孤儿进程

int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork error:");
		exit(1);
	}
	else if(pid==0)
	{
		//child
		printf("I am the child process.\n");
		printf("pid: %d,ppid: %d\n",getpid(),getppid());
		printf("after 5 second\n");//睡眠5秒，让父进程先退出
		sleep(5);

		printf("pid: %d,ppid: %d\n",getpid(),getppid());
		printf("child process is exited.\n");
	}
	else
	{
		printf("I am father process\n");
		sleep(1);
		printf("father process is exited.\n");
	}
	return 0;
}
