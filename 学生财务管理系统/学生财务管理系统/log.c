#include "log.h"
#include<string.h>
#include<stdio.h>
#include "bill.h"
#include "timer.h"
#include "user.h"
#include "safe.h"
#include<stdlib.h>

/**********************************
[函数名] fwrite_log
[传入参数] 加载到的日志结构体地址指针
[返回值] 无
[函数功能] 写入日志
[调用非库函数] encryption
[头文件的使用] <stdio.h>;"safe.h"
*********************************/
void fwrite_log(Log* loglist)
{
	FILE *fp = fopen("log.log", "w");
	Log *log = loglist;
	while (log != NULL)
	{
		encryption(log->date);//加密日期
		encryption(log->explain);//加密说明
		fputc('!', fp);//写入时多写入一个无用字符，使得判断文件尾部时使用fgetc不会产生影响
		fprintf(fp, "%s", log->date);//添加日期
		fprintf(fp, "%f", log->overage_change);//添加变动额度
		fprintf(fp, "%s\n", log->explain);//添加说明
		log = log->next;
	}
	fclose(fp);
}

/******************************
[函数名] free_loglist
[传入参数] 加载到的日志链表首指针
[返回值] 无
[函数功能] 释放链表空间
[调用非库函数] 无
[头文件的使用] <stdio.h>
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
[函数名] fread_log
[传入参数] 无
[返回值] 日志结构体指针
[函数功能] 将用户信息读取为链表结构，加载所有用户
[调用非库函数] decrption
[头文件的使用] <stdio.h>;"safe.h"
********************************************/
Log* fread_log()//读取所有账户，并在堆区用链表方式存储，返回链表头指针
{
	FILE *fp = fopen("log.log", "r");//账户文件读写
	if (fp == NULL)//文件不存在时新建文件
	{
		printf("\"log.log\"文件被删除移动或不存在，将丢失原来的所有信息，已经为您重新创建\n");
		fp = fopen("log.log", "w");
		fclose(fp);
		fp = fopen("log.log", "r");
	}
	if (fp == NULL)//文件读取失败
	{
		printf("未知错误!,账户文件打开失败\n\n");
		return NULL;
	}
	Log *head = (Log*)malloc(sizeof(Log));
	head->next = NULL;
	Log *p = head;//尾指针p,指向最后一个节点
	while (fgetc(fp) != EOF)
	{
		Log* newlog = (Log*)malloc(sizeof(Log));//创建新的节点
		fgets(newlog->date, 26, fp);//日期
		fscanf(fp, "%lf", &newlog->overage_change);//余额变动
		fgets(newlog->explain, 500, fp);//说明
		newlog->explain[strlen(newlog->explain) - 1] = '\0';//去掉多读取的字符
		decrption(newlog->date);
		decrption(newlog->explain);//对文件信息进行解析
		newlog->next = NULL;
		p->next = newlog;//将新的信息加入到链表尾部
		p = p->next;//更新尾指针p
	}
	p = head;
	head = head->next;
	free(p);//释放掉表头的标志节点
	fclose(fp);
	return head;//返回链表头指针，不含标志节点
}


/***********************************************************
[函数名] fclear_log
[传入参数] 无
[返回值] 无
[函数功能] 清除日志
[调用非库函数] get_time;fwrite_log;fread_log;free_userlist
[头文件的使用] <stdio.h>;"user.h";"timer.h"
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
	FILE *fp = fopen("log.log", "w");//账户文件读写
	if (fp == NULL)//文件读取失败
	{
		printf("未知错误!,账户文件打开失败\n\n");
		return;
	}
	Log history;
	strcpy(history.date, get_time());
	history.overage_change=money;
	history.next = NULL;
	strcpy(history.explain, "上次结余金额");
	fwrite_log(&history);
	Log* log = fread_log();
	free_userlist(p);
	fclose(fp);
	printf("操作成功\n\n\n\n\n\n");
}

/*************************************
[函数名] fprint_log
[传入参数] 无
[返回值] 无
[函数功能] 打印日志
[调用非库函数] free_loglist;fread_log;
[头文件的使用] <stdio.h>
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