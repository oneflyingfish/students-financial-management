#include "log.h"
#include<string.h>
#include<stdio.h>
#include "bill.h"
#include "timer.h"
#include "user.h"
#include "safe.h"
#include<stdlib.h>

/**********************************
[������] fwrite_log
[�������] ���ص�����־�ṹ���ַָ��
[����ֵ] ��
[��������] д����־
[���÷ǿ⺯��] encryption
[ͷ�ļ���ʹ��] <stdio.h>;"safe.h"
*********************************/
void fwrite_log(Log* loglist)
{
	FILE *fp = fopen("log.log", "w");
	Log *log = loglist;
	while (log != NULL)
	{
		encryption(log->date);//��������
		encryption(log->explain);//����˵��
		fputc('!', fp);//д��ʱ��д��һ�������ַ���ʹ���ж��ļ�β��ʱʹ��fgetc�������Ӱ��
		fprintf(fp, "%s", log->date);//�������
		fprintf(fp, "%f", log->overage_change);//��ӱ䶯���
		fprintf(fp, "%s\n", log->explain);//���˵��
		log = log->next;
	}
	fclose(fp);
}

/******************************
[������] free_loglist
[�������] ���ص�����־������ָ��
[����ֵ] ��
[��������] �ͷ�����ռ�
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>
*******************************/
void free_loglist(Log* loglist)
{
	Log *p = loglist;
	while (p != NULL)
	{
		loglist = loglist->next;
		free(p);
		p = loglist;
	}
}

/*******************************************
[������] fread_log
[�������] ��
[����ֵ] ��־�ṹ��ָ��
[��������] ���û���Ϣ��ȡΪ����ṹ�����������û�
[���÷ǿ⺯��] decrption
[ͷ�ļ���ʹ��] <stdio.h>;"safe.h"
********************************************/
Log* fread_log()//��ȡ�����˻������ڶ���������ʽ�洢����������ͷָ��
{
	FILE *fp = fopen("log.log", "r");//�˻��ļ���д
	if (fp == NULL)//�ļ�������ʱ�½��ļ�
	{
		printf("\"log.log\"�ļ���ɾ���ƶ��򲻴��ڣ�����ʧԭ����������Ϣ���Ѿ�Ϊ�����´���\n");
		fp = fopen("log.log", "w");
		fclose(fp);
		fp = fopen("log.log", "r");
	}
	if (fp == NULL)//�ļ���ȡʧ��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n\n");
		return NULL;
	}
	Log *head = (Log*)malloc(sizeof(Log));
	head->next = NULL;
	Log *p = head;//βָ��p,ָ�����һ���ڵ�
	while (fgetc(fp) != EOF)
	{
		Log* newlog = (Log*)malloc(sizeof(Log));//�����µĽڵ�
		fgets(newlog->date, 26, fp);//����
		fscanf(fp, "%lf", &newlog->overage_change);//���䶯
		fgets(newlog->explain, 500, fp);//˵��
		newlog->explain[strlen(newlog->explain) - 1] = '\0';//ȥ�����ȡ���ַ�
		decrption(newlog->date);
		decrption(newlog->explain);//���ļ���Ϣ���н���
		newlog->next = NULL;
		p->next = newlog;//���µ���Ϣ���뵽����β��
		p = p->next;//����βָ��p
	}
	p = head;
	head = head->next;
	free(p);//�ͷŵ���ͷ�ı�־�ڵ�
	fclose(fp);
	return head;//��������ͷָ�룬������־�ڵ�
}


/***********************************************************
[������] fclear_log
[�������] ��
[����ֵ] ��
[��������] �����־
[���÷ǿ⺯��] get_time;fwrite_log;fread_log;free_userlist
[ͷ�ļ���ʹ��] <stdio.h>;"user.h";"timer.h"
***********************************************************/
void fclear_log()
{
	double money = 0.00;
	User *p = fread_users();
	User *t = p->next;
	while (t != NULL) 
	{
		money = money + t->overage;
		t = t->next;
	}
	FILE *fp = fopen("log.log", "w");//�˻��ļ���д
	if (fp == NULL)//�ļ���ȡʧ��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n\n");
		return;
	}
	Log history;
	strcpy(history.date, get_time());
	history.overage_change=money;
	history.next = NULL;
	strcpy(history.explain, "�ϴν�����");
	fwrite_log(&history);
	Log* log = fread_log();
	free_userlist(p);
	fclose(fp);
	printf("�����ɹ�\n\n\n\n\n\n");
}

/*************************************
[������] fprint_log
[�������] ��
[����ֵ] ��
[��������] ��ӡ��־
[���÷ǿ⺯��] free_loglist;fread_log;
[ͷ�ļ���ʹ��] <stdio.h>
***************************************/
void fprint_log()
{
	Log *log = fread_log();
	Log *p = log;
	while(p != NULL)
	{
		printf("%-28s", p->date);
		printf("%-9.2f   ", p->overage_change);
		printf("%s\n", p->explain);
		p = p->next;
	}
	printf("\n\n\n\n\n\n");
	free_loglist(log);
}