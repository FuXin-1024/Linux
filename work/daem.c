/*************************************************************************
	> File Name: daem.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 11 Jul 2017 09:56:55 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

void create_daemon()
{
	umask(0);   //1.设置umask为0
	pid_t pid = fork();  //2.fork出子进程，终止父进程后，子进程调用setsid创建新的会话
	if(pid < 0)
	{
		perror("pid");
		return ;
	}
	else if(pid > 0)
	{
		exit(0);//终止父进程
	}
	setsid();

	//3.设置当前的工作目录为根目录
	if(chdir("/") < 0)
	{
		perror("chdir error");
		return;
	}
	//4.关闭文件描述表
	close(0);
	close(1);
	close(2);
	//5.忽略SIG_CHLD信号
	signal(SIGCHLD,SIG_IGN);
}

int main()
{
	create_daemon();
	while(1)
		sleep(1);
	return 0;
}

