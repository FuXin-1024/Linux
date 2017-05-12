/*************************************************************************
	> File Name: Zombies.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Wed 10 May 2017 09:39:47 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid==0)
	{
		//child
		printf("child is exiting!\n");
	}
	else
	{
		//father
		sleep(5);
		system(" ps -o pid,ppid,state,tty,command");
		printf("father is exiting!\n");
	}
	return 0;
}
