/*************************************************************************
	> File Name: argc.c
	> Author: fx
	> Mail: 1007160080@qq.com 
	> Created Time: Sat 06 May 2017 02:20:35 AM PDT
 ************************************************************************/

#include<stdio.h>
void main(int argc,char** argv)
{
	printf("argc:%d\n",argc);
	printf("argv[0]:%s\n",argv[0]);
	printf("argv[1]:%s\n",argv[1]);
	printf("argv[2]:%s\n",argv[2]);
}
