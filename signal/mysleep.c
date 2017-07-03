/*************************************************************************
	> File Name: mysleep.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Sun 02 Jul 2017 03:39:37 AM PDT
 ************************************************************************/


#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_run(int signo)
{
	//DO NOTOING
}

int mysleep(int secs)
{
	struct sigaction sig,osig;
	//设置sugaction的属性
	sig.sa_handler = sig_run;//设置处理函数
	sigemptyset(&sig.sa_mask);//将表示阻塞的标记初始化为零
	sig.sa_flags = 0;
	sigaction(SIGALRM,&sig,&osig);

	alarm(secs);//设置闹钟，等待闹钟secs秒后，发送SIGALRM信号
	pause();//进程挂起直到有信号递达
	int ret = alarm(0);//清除闹钟，并保存函数返回值，与sleep函数值一致

	sigaction(SIGALRM,&osig,NULL);//将SIGALRM信号的处理方式设置成osig
	return ret;
}

int main()
{
	while(1)
	{
		mysleep(10);
		printf("Hello World!\n");
	}
	return 0;
}
