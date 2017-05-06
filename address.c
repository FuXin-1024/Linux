#include<stdlib.h>
#include<stdio.h>

int g_val;

void test()
{
	int a=10;
	int b=20;
	printf("test stack1 addres:0x%x \n",&a);
	printf("test stack1 addres:0x%x \n",&b);
}
void (*fp)();

int main()
{
	int a=10;
	int *heap=malloc(sizeof(int));
	fp=test;
	printf("code address: 0x%x\n",fp);
	printf("data address: 0x%x\n",&g_val);
	printf("heap address: 0x%x\n",heap);
	printf("main stack0 address: 0x%x\n",&a);
	return 0;
}
