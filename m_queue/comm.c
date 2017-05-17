/*************************************************************************
	> File Name: comm.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Wed 17 May 2017 07:43:59 AM PDT
 ************************************************************************/

#include<stdio.h>
#include"comm.h"

const int g_ser_send_type=1;//serve
const int g_cli_send_type=2;//client

void print_log(char* msg)
{
	print("%s[%d]:%s\n",__FUNCTION__,__LINE__,msg);
}
