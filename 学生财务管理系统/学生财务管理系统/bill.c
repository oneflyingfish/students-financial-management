#include "bill.h"
#include "admin_account.h"
#include "User.h"
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "log.h"
#include <stdlib.h>

/******************************************************************************************88
[������]incount_inorder
[�������] ��
[����ֵ] ��
[��������]��ĳһ��ѧ�����е�������
[���÷ǿ⺯��] fread_users,loc_user,fwrite_user_list;free_userlist;
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void incount_inorder()
{
	char a[12];
	User *userlist = fread_users(),*p;
	float b;
	int judge;
	printf("��������ϣ���������˻�ѧ�Ż�������:");
	while (1)//����˻�
	{
		gets_s(a,12);//����û�������˻�
		if (strcmp(a, "0000") == 0)//�û����������˻�����ǰ�˳�
		{
			return;
		}
		else if (loc_user(a, userlist) == NULL)//�û���������
		{
			printf("��������˻������ڣ��˳�������\"0000\")�����������룺");
			continue;
		}
		else//�˻��Ϸ�
		{
			break;
		}
	}
	printf("���������˽��:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("�ý��С��0��������Ϊ������֧��������ȷ�ϲ�������1��ȡ����������������0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("ָ���������������:");
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
			printf("���ٴ��������˽��:");
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
[������]outcount_inorder
[�������] ��
[����ֵ] ��
[��������]��ĳһ��ѧ�����е�������
[���÷ǿ⺯��] fread_users,loc_user,fwrite_user_list;free_userlist;
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
*******************************************************************/
void outcount_inorder()
{
	char a[12];
	User *userlist = fread_users(), *p;
	float b;
	int judge;
	printf("��������ϣ���������˻�ѧ�Ż�������:");
	while (1)//����˻�
	{
		gets_s(a,12);//����û�������˻�
		if (strcmp(a, "0000") == 0)//�û����������˻�����ǰ�˳�
		{
			return;
		}
		else if (loc_user(a, userlist) == NULL)//�û���������
		{
			printf("��������˻������ڣ��˳�������\"0000\")�����������룺");
			continue;
		}
		else//�˻��Ϸ�
		{
			break;
		}
	}
	printf("������۳����:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("�ý��С��0��������Ϊ�����д��˲�����ȷ�ϲ�������1��ȡ������������������������0��");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("ָ���������������:");
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
			printf("���ٴ�����֧�����:");
			continue;
		}
		break;
	}
	p = loc_user(a, userlist);
	p->overage -= b;
	fwrite_user_list(userlist);
	free_userlist(userlist);
	printf("�����ɹ���\n\n");
	return;
}





/*******************************************
[������]user_arrearage
[�������] ��
[����ֵ] ��
[��������]δ�����û������ֺ��û�������
[���÷ǿ⺯��] fread_users,free_userlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
********************************************/
void user_arrearage()
{
	double t;
	printf("����ΪǷ���û���\n");
	User *p=fread_users();//�ҵ�׿Խ��
	User *s=p->next;//��׿Խ���ĵ�һ��ͬѧ��ʼ
	while(s!=NULL){//��������
		if(s->overage<p->overage) 
		{
			printf("%-14s ", s->STU_ID);
			printf("%-8s ",s->name);
			t=-(s->overage)+(p->overage);
			printf("������ȡ��%-6.2f\n",t);
		}
		s=s->next;
	}
	free_userlist(p);
	printf("\n");
}

/**********************************************
[������]allaccount_administor
[�������] ��
[����ֵ] ��
[��������]����ѧ�Ż�������ѯ���
[���÷ǿ⺯��] fread_users,free_userlist,loc_user
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
************************************************/
void allaccount_administor()
{ 
	char a[12];
	printf("��������Ҫ��ѯ�û���ѧ�Ż���������");
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
		printf("����ĵ��û������ڣ���\n");
		printf("�������ٴ���Ҫ��ѯ�û���ѧ�Ż�������(\"0000\"������������");
		goto LOOP2;
		return ;
	}
	printf("%-14s ", s->STU_ID);
	printf("%-8s ", s->name);
	printf("��%-6.2f\n", s->overage);
	free_userlist(p);
	printf("\n");
	return;
}


/************************************************
[������]arrearage_situation
[�������] ��
[����ֵ] ��
[��������]Ƿ��ѧ�����������绰���
[���÷ǿ⺯��] fread_users,free_userlist,loc_user
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
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
			printf("�绰:%-14s",s->phone);
			printf("Ƿ�ѣ�%6.2f\n",-s->overage);
			i++;		
		}
		s = s->next;
	}
	if (i == 0)
	{
		printf("��\n");
	}
	free_userlist(p);
	printf("\n");
	return;
}


/*************************************
[������]arrearage_situation
[�������] ��
[����ֵ] ��
[��������]��ʾ�༶��������
[���÷ǿ⺯��] fread_users,free_userlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
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
	printf("ȫ������%.2f\n\n\n\n\n\n", money);
	free_userlist(p);
	return;
}

/*************************************
[������]arrearage_situation
[�������] ��
[����ֵ] ��
[��������] �������ˣ����г������û�����û�ͬʱ��������һ�����
[���÷ǿ⺯��] fread_users,free_userlist��fwrite_user_list
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/

void incount_inqueue() {
	float a;
	int judge;
	printf("�����뵥�˴���Ľ���һ����Ϊ�����û�ִ�д��������:");
	while (1)
	{
		scanf("%f", &a);
		if (a<0)
		{
			printf("�ý��С��0��������Ϊ������ȫ����֧��������ȷ�ϲ�������1��ȡ������������������������0����");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("ָ���������������:");
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
			printf("���ٴ��������˽��:");
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
	printf("�����ɹ���\n\n\n\n\n\n");
	return;
}


/*************************************
[������]arrearage_situation
[�������] float�Ͳα���
[����ֵ] ��
[��������] ������ˣ���ѵ�֧���������˹�ͬ�е�
[���÷ǿ⺯��] fread_users,free_userlist��fwrite_user_list
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";
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
[������]setup_log1
[�������] ��
[����ֵ] ��
[��������] ����������־
[���÷ǿ⺯��] fread_users,free_userlist,get_time,fread_log,fwrite_log,free_loglist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log1() 
{
	Log *log = (Log*)malloc(sizeof(Log));
	log->next = NULL;
	User *userlist = fread_users();
	float b;
	int judge;
	printf("�������շѽ��:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("�ý��С��0��������Ϊ������֧��������ȷ�ϲ�������1��ȡ����������������0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("ָ���������������:");
				}
				else if (judge == 1)
				{
					printf("������˴����˵�˵����");
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
					printf("�����ɹ�\n\n\n\n\n\n");
					return;
				}
				else
				{
					break;
				}
			}
			printf("���ٴ��������˽��:");
			continue;
		}
		else
		{
			break;
		}
	}
	printf("������˴����˵�˵����");
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
	printf("�����ɹ�\n\n\n\n\n\n");
	return;
}

/*************************************
[������]setup_log2
[�������] ��
[����ֵ] ��
[��������] ����������־
[���÷ǿ⺯��] fread_users,free_userlist��fwrite_user_list,get_time,fread_log,fwrite_log,free_loglist,outaccount_inqueue
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log2() 
{
	Log *log=(Log*)malloc(sizeof(Log));
	log->next = NULL;
	float b;
	int judge;
	printf("������֧�����:");
	while (1)
	{
		scanf("%f", &b);
		if (b < 0)
		{
			printf("�ý��С��0��������Ϊ���������˲�����ȷ�ϲ�������1��ȡ����������������0):");
			while (1)
			{
				scanf("%d", &judge);
				if (judge != 1 && judge != 0)
				{
					printf("ָ���������������:");
				}
				else if (judge == 1)
				{
					printf("������˴�֧����˵����");
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
					printf("�����ɹ�\n\n\n\n\n\n");
					return;
				}
				else
				{
					break;
				}
			}
			printf("���ٴ�����֧�����:");
			continue;
		}
		else
		{
			break;
		}
	}
	
	printf("������˴�֧����˵����");
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
	printf("�����ɹ�\n\n\n\n\n\n");
	return;
}