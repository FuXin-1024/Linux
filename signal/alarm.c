/*************************************************************************
	> File Name: alarm.c
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Sat 01 Jul 2017 03:06:23 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
	int count = 15;
	alarm(1);
	for(;1;count++)
	{
		printf("count = %d\n",count);
	}
	return 0;
}
