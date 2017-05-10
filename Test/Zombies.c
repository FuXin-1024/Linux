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
	pid_t pid=getpid();
	pid_t id=fork();
	if(-1==id)
	{
		printf("fork error!return code is:%d\n",errno);
		return 2;
	}
	else if(0==id)
	{
		//child
		printf("child pid is:%d\n",getpid());
		exit(3);
	}
	else
	{
		//father
		printf("father pid is:%d.return pidis:%d\n",getpid(),id);
		sleep(30);
	}
	return 0;
}
