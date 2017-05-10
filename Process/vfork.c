/*************************************************************************
	> File Name: vfork.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Wed 10 May 2017 03:27:05 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include<unistd.h>

int g_var=6;
int main()
{
	int var=88;
	pid_t pid=vfork();
	printf("before vfork\n");

	if(pid<0)
	{
		printf("vfork error");
	}
	else if(pid==0)
	{
		//child
		g_var++;
		var++;
		_exit(0);
	}

	//father continues here
	printf("pid=%d,g_var=%d,var=%d\n",pid,g_var,var);
	return 0;

}
