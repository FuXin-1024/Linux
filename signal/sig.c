/*************************************************************************
	> File Name: sig.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Sat 01 Jul 2017 04:01:22 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void Printsigset(sigset_t *set)
{
	int i = 0;
	for(;i<32;i++)
	{
		if(sigismember(set ,i))//判断指定信号是否在目标集合中
		{
			putchar('1');
		}
		else
		{
			putchar('0');
		}
	}
	puts("");
}

int main()
{
	sigset_t s,p;
	sigemptyset(&s); //定义信号集，并清空初始化
	sigaddset(&s,SIGINT); //添加Ctrl+C信号
	sigprocmask(SIG_BLOCK,&s,NULL); //设置阻塞信号集，阻塞SIGINT信号
	while(1)
	{
		sigpending(&p); //获取未决信号集
		Printsigset(&p);
		sleep(1);
	}
	return 0;
}

