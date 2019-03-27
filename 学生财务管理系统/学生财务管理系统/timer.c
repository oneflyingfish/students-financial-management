#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<stdlib.h>
#include "timer.h"

/*****************************
[函数名] get_time
[传入参数] 无
[返回值] 时间的字符数组首地址
[函数功能] 获取当前时间
[调用非库函数] 无
[头文件的包含] <time.h>
*********************************/
char* get_time()
{
	time_t num_time;										//定义一个时间类型变量
	time(&num_time);										//获取当前时间对应的数字
	struct tm * time_now;									//定义当前时间类型的结构体，存储当前时间
	time_now = localtime(&num_time);						//将获得的时间转化为本地时间，返回给time_now
	char *p = (char*)malloc(sizeof(char) * 40);				//目标字符串
	strftime(p, 40, "%Y-%m-%d  /%w   %H:%M:%S",time_now);	//将当前时间按照一定格式存储
	return p;
}