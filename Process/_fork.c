/*************************************************************************
	> File Name: _fork.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Wed 10 May 2017 02:19:59 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
//验证子进程对变量所改变，不影响父进程该变量的值
int g_val=6;
char buf[]="a write to stdout\n";

int main()
{
	int var=88;
	pid_t pid=fork();
	
	if(pid<0)
	{
		printf("fork error");
	}
	else if(pid==0)
	{
		//child
		g_val++;
		var++;
	}
	else
	{
		//father
		sleep(5);
	}
	printf("pid=%d,g_val=%d,var=%d\n",pid,g_val,var);
	return 0;


