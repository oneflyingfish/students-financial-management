#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<stdlib.h>
#include "timer.h"

/*****************************
[������] get_time
[�������] ��
[����ֵ] ʱ����ַ������׵�ַ
[��������] ��ȡ��ǰʱ��
[���÷ǿ⺯��] ��
[ͷ�ļ��İ���] <time.h>
*********************************/
char* get_time()
{
	time_t num_time;										//����һ��ʱ�����ͱ���
	time(&num_time);										//��ȡ��ǰʱ���Ӧ������
	struct tm * time_now;									//���嵱ǰʱ�����͵Ľṹ�壬�洢��ǰʱ��
	time_now = localtime(&num_time);						//����õ�ʱ��ת��Ϊ����ʱ�䣬���ظ�time_now
	char *p = (char*)malloc(sizeof(char) * 40);				//Ŀ���ַ���
	strftime(p, 40, "%Y-%m-%d  /%w   %H:%M:%S",time_now);	//����ǰʱ�䰴��һ����ʽ�洢
	return p;
}