/*************************************************************************
	> File Name: comm.h
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Tue 16 May 2017 01:34:07 PM PDT
 ************************************************************************/

#ifndef __COMM__
#define __COMM__

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

#define __MSG_SIZE__ 1024
#define FILEPATH "./.msg"
#define ID 0
extern const int g_ser_send_type;//server
extern const int g_cli_send-type;//client

typedef strut _msginfo
{
	long mtype;
	char mtext[__MSG_SIZE__];
}msginfo;

void print_log(char *);
#endif;