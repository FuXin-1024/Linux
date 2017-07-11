/*************************************************************************
	> File Name: reentry.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Tue 11 Jul 2017 08:08:12 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

int g_val = 0;

void fun()
{
	int i = 3;
	while(i--)
	{
		g_val++;
		printf("g_val = %d\n",g_val);
		sleep(1);
	}
}

int main()
{
	signal(2,fun); //捕捉2号信号，执行自定义函数fun()
	fun();
	printf("main: g_val = %d\n",g_val);
	return 0;
}
