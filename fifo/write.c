/*************************************************************************
	> File Name: write.c
	> Author: fx
	> Mail: 1007160080@qq..com 
	> Created Time: Mon 15 May 2017 01:04:01 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define _PATH_ "./myfifo"
#define _SIZE_ 100

int main()
{
	int ret=mkfifo(_PATH_,0666|S_IFIFO);
	if (ret == -1)
	{
		perror("mkfifo error!");
		return 1;
	}

	int fd=open(_PATH_,O_WRONLY);
	if(fd<0)
	{
		printf("open file error!\n");
		return 2;
	}
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	while(1)
	{
		read(0,buf,sizeof(buf));
		int ret=write(fd,buf,strlen(buf)-1);
		buf[ret]='\0';
		if(ret<0)
		{
			printf("wirte error!\n");
			break;
		}
	
		if(strncmp(buf,"quit",4)==0)
		{
			break;
		}
	}
	close(fd);
	return 0;
}
