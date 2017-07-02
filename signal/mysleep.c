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
	sig.sa_handler = sig_run;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGALRM,&sig,&osig);

	alarm(secs);
	pause();
	int ret = alarm(0);

	sigaction(SIGALRM,&osig,NULL);
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
