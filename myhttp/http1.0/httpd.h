/*************************************************************************
	> File Name: httpd.h
	> Author: fx
	> Mail: 1007160080qq.com 
	> Created Time: Fri 18 Aug 2017 07:43:26 AM PDT
 ************************************************************************/

#ifndef __HTTPD_H_
#define __HTTPD_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<assert.h>
#include<ctype.h>
#include<string.h>

#define WARNING 1
#define FATAL 2
#define SIZE 102400

void print_log(const char* str,int error);
int startup(const char* ip,const char* port);
int get_line(int sock,char* buf,int size);
void Dealwithsock(int sock);

#endif

