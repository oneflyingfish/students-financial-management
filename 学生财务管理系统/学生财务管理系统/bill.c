#include "bill.h"
#include "admin_account.h"
#include "User.h"
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "log.h"
#include <stdlib.h>

/******************************************************************************************88
[函数名]incount_inorder
[传入参数] 无
[返回值] 无
[函数功能]对某一个学生进行单独入账
[调用非库函数] fread_users,loc_user,fwrite_user_list;free_userlist;
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void incount_inorder()
{
	char a[12];
	User *userlist = fread_users(),*p;
	float b;
	int judge;
	printf("请输入您希望操作的账户学号或者姓名:");
	while (1)//获得账户
	{
		gets_s(a,12);//获得用户输入的账户
		if (strcmp(a, "0000") == 0)//用户放弃创建账户，提前退出
		{
			return;
		}
		else if (loc_user(a, userlist) == NULL)//用户名不存在
		{
			printf("您输入的账户不存在（退出请输入\"0000\")，请重新输入：");
			continue;
		}
		else//账户合法
		{
			break;
		}
	}
	printf("请输入入账金额:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("该金额小于0，将可能为您进行支出操作（确认操作输入1，取消操作并重新输入0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("指令错误，请重新输入:");
				}
				else if (judge == 1)
				{
					p = loc_user(a, userlist);
					p->overage += b;
					free_userlist(userlist);
					return;
				}
				else
				{
					break;
				}
			}
			printf("请再次输入入账金额:");
			continue;
		}
		break;
	}
	p = loc_user(a, userlist);
	p->overage += b;
	fwrite_user_list(userlist);
	free_userlist(userlist);
	return;
}


/******************************************************************
[函数名]outcount_inorder
[传入参数] 无
[返回值] 无
[函数功能]对某一个学生进行单独出账
[调用非库函数] fread_users,loc_user,fwrite_user_list;free_userlist;
[头文件的使用] <stdio.h>;<string.h>;"User.h";
*******************************************************************/
void outcount_inorder()
{
	char a[12];
	User *userlist = fread_users(), *p;
	float b;
	int judge;
	printf("请输入您希望操作的账户学号或者姓名:");
	while (1)//获得账户
	{
		gets_s(a,12);//获得用户输入的账户
		if (strcmp(a, "0000") == 0)//用户放弃创建账户，提前退出
		{
			return;
		}
		else if (loc_user(a, userlist) == NULL)//用户名不存在
		{
			printf("您输入的账户不存在（退出请输入\"0000\")，请重新输入：");
			continue;
		}
		else//账户合法
		{
			break;
		}
	}
	printf("请输入扣除金额:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("该金额小于0，将可能为您进行存账操作（确认操作输入1，取消操作并重新输入金额请输入0）");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("指令错误，请重新输入:");
				}
				else if (judge == 1)
				{
					p = loc_user(a, userlist);
					p->overage -= b;
					free_userlist(userlist);
					return;
				}
				else
				{
					break;
				}
			}
			printf("请再次输入支付金额:");
			continue;
		}
		break;
	}
	p = loc_user(a, userlist);
	p->overage -= b;
	fwrite_user_list(userlist);
	free_userlist(userlist);
	printf("操作成功！\n\n");
	return;
}





/*******************************************
[函数名]user_arrearage
[传入参数] 无
[返回值] 无
[函数功能]未交费用户的名字和用户所差金额
[调用非库函数] fread_users,free_userlist
[头文件的使用] <stdio.h>;<string.h>;"User.h";
********************************************/
void user_arrearage()
{
	double t;
	printf("以下为欠费用户：\n");
	User *p=fread_users();//找到卓越班
	User *s=p->next;//重卓越班后的第一个同学开始
	while(s!=NULL){//遍历链表
		if(s->overage<p->overage) 
		{
			printf("%-14s ", s->STU_ID);
			printf("%-8s ",s->name);
			t=-(s->overage)+(p->overage);
			printf("还需收取：%-6.2f\n",t);
		}
		s=s->next;
	}
	free_userlist(p);
	printf("\n");
}

/**********************************************
[函数名]allaccount_administor
[传入参数] 无
[返回值] 无
[函数功能]根据学号或姓名查询余额
[调用非库函数] fread_users,free_userlist,loc_user
[头文件的使用] <stdio.h>;<string.h>;"User.h";
************************************************/
void allaccount_administor()
{ 
	char a[12];
	printf("请输入需要查询用户的学号或者姓名：");
	LOOP2:
	scanf("%s", a);
	if (strcmp(a, "0000") == 0)
	{
		return;
	}
	float money=0;
    User *p=fread_users();
	User *s=loc_user(a,p);
	if (s == NULL) 
	{
		printf("你查阅的用户不存在！！\n");
		printf("请输入再次需要查询用户的学号或者姓名(\"0000\"结束操作）：");
		goto LOOP2;
		return ;
	}
	printf("%-14s ", s->STU_ID);
	printf("%-8s ", s->name);
	printf("余额：%-6.2f\n", s->overage);
	free_userlist(p);
	printf("\n");
	return;
}


/************************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能]欠费学生的姓名，电话输出
[调用非库函数] fread_users,free_userlist,loc_user
[头文件的使用] <stdio.h>;<string.h>;"User.h";
*************************************************/
void arrearage_situation()
{
	User *p=fread_users();
	User *s=p->next;
	int i = 0;
	while(s!=NULL)
	{
		if(s->overage<0){
			printf("%-14s",s->name);
			printf("%-14s",s->STU_ID);
			printf("电话:%-14s",s->phone);
			printf("欠费：%6.2f\n",-s->overage);
			i++;		
		}
		s = s->next;
	}
	if (i == 0)
	{
		printf("无\n");
	}
	free_userlist(p);
	printf("\n");
	return;
}


/*************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能]显示班级班费总余额
[调用非库函数] fread_users,free_userlist
[头文件的使用] <stdio.h>;<string.h>;"User.h";
**********************************************/
void allaccount_visitor() 
{   
	double money = 0.00;
	User *p = fread_users();
	User *t = p->next;
	while (t != NULL) {
		money = money + t->overage;
		t = t->next;
	}
	printf("全班总余额：%.2f\n\n\n\n\n\n", money);
	free_userlist(p);
	return;
}

/*************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能] 集体入账，所有除对照用户外的用户同时存入或输出一个金额
[调用非库函数] fread_users,free_userlist，fwrite_user_list
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/

void incount_inqueue() {
	float a;
	int judge;
	printf("请输入单人存入的金额（将一次性为所有用户执行存入操作）:");
	while (1)
	{
		scanf("%f", &a);
		if (a<0)
		{
			printf("该金额小于0，将可能为您进行全班性支出操作（确认操作输入1，取消操作并重新输入金额请输入0）：");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("指令错误，请重新输入:");
				}
				else if (judge == 1)
				{
					User *p = fread_users();
					User *s = p->next;
					while (s != NULL)
					{
						s->overage += a;
						s = s->next;
					}
					free_userlist(p);
					return;
				}
				else
				{
					break;
				}
			}
			printf("请再次输入入账金额:");
			continue;
		}
		break;
	}
	User *p = fread_users();
	User *s = p->next;
	while (s != NULL)
	{
		s->overage += a;
		s = s->next;
	}
	fwrite_user_list(p);
	free_userlist(p);
	printf("操作成功！\n\n\n\n\n\n");
	return;
}


/*************************************
[函数名]arrearage_situation
[传入参数] float型参变量
[返回值] 无
[函数功能] 集体出账，班费的支出由所有人共同承担
[调用非库函数] fread_users,free_userlist，fwrite_user_list
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void outaccount_inqueue(float t) {
	int num=0;
	User *p = fread_users();
	User *s = p->next;
	while (s != NULL)
	{
		s = s->next;
		num++;
	}
	s = p;
	while (s != NULL) {
		s->overage -= t*1.0 / num;
		s = s->next;
	}
	fwrite_user_list(p);
	free_userlist(p);
	return;
}

/*************************************
[函数名]setup_log1
[传入参数] 无
[返回值] 无
[函数功能] 建立入账日志
[调用非库函数] fread_users,free_userlist,get_time,fread_log,fwrite_log,free_loglist
[头文件的使用] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log1() 
{
	Log *log = (Log*)malloc(sizeof(Log));
	log->next = NULL;
	User *userlist = fread_users();
	float b;
	int judge;
	printf("请输入收费金额:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("该金额小于0，将可能为您进行支出操作（确认操作输入1，取消操作并重新输入0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("指令错误，请重新输入:");
				}
				else if (judge == 1)
				{
					printf("请输入此次收账的说明：");
					gets_s(log->explain,500);
					log->overage_change = b;
					strcpy(log->date, get_time());
					Log *loglist = fread_log();
					Log *q = loglist;
					if (loglist == NULL)
					{
						loglist = log;
					}
					else
					{
						while (q->next != NULL)
						{
							q = q->next;
						}
						q->next = log;
					}
					fwrite_log(loglist);
					free_loglist(loglist);
					userlist->overage += b;
					free_userlist(userlist);
					printf("操作成功\n\n\n\n\n\n");
					return;
				}
				else
				{
					break;
				}
			}
			printf("请再次输入收账金额:");
			continue;
		}
		else
		{
			break;
		}
	}
	printf("请输入此次收账的说明：");
	getchar();
	gets_s(log->explain,500);
	log->overage_change = b;
	strcpy(log->date, get_time());
	Log *loglist = fread_log();
	Log *q = loglist;
	if (loglist == NULL)
	{
		loglist = log;
	}
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = log;
	}
	fwrite_log(loglist);
	free_loglist(loglist);
	userlist->overage += b;
	fwrite_user_list(userlist);
	free_userlist(userlist);
	printf("操作成功\n\n\n\n\n\n");
	return;
}

/*************************************
[函数名]setup_log2
[传入参数] 无
[返回值] 无
[函数功能] 建立入账日志
[调用非库函数] fread_users,free_userlist，fwrite_user_list,get_time,fread_log,fwrite_log,free_loglist,outaccount_inqueue
[头文件的使用] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log2() 
{
	Log *log=(Log*)malloc(sizeof(Log));
	log->next = NULL;
	float b;
	int judge;
	printf("请输入支出金额:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("该金额小于0，将可能为您进行入账操作（确认操作输入1，取消操作并重新输入0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("指令错误，请重新输入:");
				}
				else if (judge == 1)
				{
					printf("请输入此次支出的说明：");
					gets_s(log->explain,50);
					log->overage_change = -b;
					strcpy(log->date, get_time());
					Log *loglist = fread_log();
					Log *q = loglist;
					if (loglist == NULL)
					{
						loglist = log;
					}
					else
					{
						while (q->next != NULL)
						{
							q = q->next;
						}
						q->next = log;
					}
					fwrite_log(loglist);
					free_loglist(loglist);
					outaccount_inqueue(b);
					printf("操作成功\n\n\n\n\n\n");
					return;
				}
				else
				{
					break;
				}
			}
			printf("请再次输入支出金额:");
			continue;
		}
		else
		{
			break;
		}
	}
	
	printf("请输入此次支出的说明：");
	getchar();
	gets_s(log->explain,50);
	log->overage_change = -b;
	strcpy(log->date, get_time());
	Log *loglist = fread_log();
	Log *q = loglist;
	if (loglist == NULL)
	{
		loglist = log;
	}
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = log;
	}
	fwrite_log(loglist);
	free_loglist(loglist);
	outaccount_inqueue(b);
	printf("操作成功\n\n\n\n\n\n");
	return;
}