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
	alarm(100);
	for(;1;count++)
	{
		printf("count = %d\n",count);
		if(count==1000000)
		break;
	}
	int a = alarm(0);// 取消以前设定的闹钟，返回剩余的秒数
	printf("alarm is: %d\n",a);
	return 0;
}
