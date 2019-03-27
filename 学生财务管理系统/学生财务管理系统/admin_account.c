#include "admin_account.h"
#include "safe.h"
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4013)//����VS2017��gets�Ĳ���ȫ����
#pragma warning(disable:4267)//����VS2017��strlen����ֵ�ľ���
extern char current_account[8];


/***************************************************************************************
[������] add_account
[�������] ��
[����ֵ] ��
[��������] ������˻�
[���÷ǿ⺯��] fread_account;judge_acclegal;loc_account;fwrite_account;free_accountlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"safe.h"
******************************************************************************************/
void add_account()
{
	Account *account=(Account*)malloc(sizeof(Account));
	account->next = NULL;
	Account *accountlist = fread_account();//���������˻�
	printf("�������˻���(��λ��������ɣ���");
	char acc[10];//�����Դ���ʵ��ʹ�ã���ֹ�û����������ɴ���
	char password1[30];//�����Դ���ʵ��ʹ�ã���ֹ�û����������ɴ���(��ͬ��
	char password2[30];
	while (1)//����˻�
	{
		gets(acc);//����û�������˻�
		if (strcmp(acc, "0000") == 0)//�û����������˻�����ǰ�˳�
		{
			return;
		}
		if (judge_acclegal(acc) == 0)//������˻����ȷǷ�
		{
			printf("��������˻�������λ�����������룺");
			continue;
		}
		else if (judge_acclegal(acc) == 1)//�˻���Ϊ�����ַǷ�
		{
			printf("��������˻������������ַ������������룺");
			continue;
		}
		else if (loc_account(acc, accountlist) != NULL)//�û����Ѿ�ע��
		{
			printf("��������˻��Ѿ����ڣ��˳�������\"0000\")�����������룺");
			continue;
		}
		else//�˻��Ϸ�
		{
			break;
		}
	}
	LOOP0://������������
	printf("������8-16λ���룺");
	while (1)//���λ������
	{
		gets(password1);//��������
		if (strlen(password1) > 16 || strlen(password1) < 8)//����λ���Ƿ�
		{
			printf("�����������λ������8~16λ�������������������룺");
			continue;
		}
		else//�״���������Ϸ�
		{
			break;
		}
	}
	system("cls");
	printf("���ٴ��������룺");
	while (1)//ȷ������
	{
		gets(password2);//���ȷ�ϵ�����
		if (strcmp(password2, "0000") == 0)//�û�ѡ��������������
		{
			goto LOOP0;
		}
		else if (strcmp(password1, password2)!=0)//�����������벻��ͬ
		{
			printf("��������������벻��ȫ��ͬ(������������������룬������\"0000\")�����ٴ�ȷ����������:");
			continue;
		}
		else//ȷ������ɹ�
		{
			break;
		}
	}
	strcpy(account->str_acc, acc);
	strcpy(account->str_password, password1);

	FILE*fp = fopen("account.log", "a");
	if (fp == NULL)//�ļ������ڣ����½�ʱ��������
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n");
		return;
	}
	fwrite_account(account, fp);//׷���µ��˻�
	fclose(fp);
	free(account);
	free_accountlist(accountlist);
	system("cls");
	printf("�������\n\n\n\n\n\n");
}

/**************************************************************************
[������] delete_account
[�������] ��
[����ֵ] ��
[��������] ɾ�������˻�
[���÷ǿ⺯��] fread_account;loc_account;fwrite_account;free_accountlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
**************************************************************************/
void delete_account()//ɾ���˻�
{

	Account *accountlist = fread_account();
	printf("����������Ҫɾ�����û�����");
	char acc[10];//�����Դ���ʵ��ʹ�ã���ֹ�û����������ɴ���
	char password[30];//�����Դ���ʵ��ʹ�ã���ֹ�û����������ɴ���
	gets(acc);
	if (strcmp(acc, current_account) == 0)
	{
		printf("����ɾ����ǰ�˻�\n");
		return;
	}
	Account *loc = loc_account(acc, accountlist), *q;//�����Ҫɾ�����˻��ṹ��
	if (loc == NULL)
	{
		printf("�û������ڣ������˳�������\n");
		return;
	}
	printf("���������룺");
	gets(password);
	if (strcmp(loc->str_password, password) == 0)//����ȷ����ȷ������ɾ������
	{
		Account *p = accountlist;
		if (strcmp(p->str_acc, acc) == 0)
		{
			q = p;
			accountlist = accountlist->next;
			free(q);
		}
		else
		{
			while (1)
			{
				if (strcmp(p->next->str_acc, acc) == 0)
				{
					break;
				}
				p = p->next;
			}
			q = p->next;
			p->next = q->next;
			free(q);
		}
		printf("ɾ���ɹ���\n\n\n\n\n\n");
	}
	else
	{
		printf("�������Ϊ�������˻���ȫ�������˳�����\n\n\n\n\n");
		return;
	}
	FILE *fp = fopen("account.log", "w");//�˻��ļ���д
	if (fp == NULL)//�˻��ļ������ڣ������µ��ļ�д��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n");
		return;
	}
	Account *p = accountlist;
	while (p != NULL)
	{
		fwrite_account(p, fp);
		p = p->next;
	}
	free_accountlist(accountlist);
	fclose(fp);
}

/********************************************************
[������] judge_acclegal
[�������] ��Ҫ�жϵ��ַ���
[����ֵ] ���ȷǷ�����0,�˻���Ϊ������ʱ������1,//�˻��Ϸ�������2
[��������] �ж��û����Ƿ���ϱ�׼
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
*********************************************************/
int judge_acclegal(char acc[])
{
	int length = strlen(acc);//��õõ����˻��ĳ���
	if (length != 6)
	{
		return 0;
	}//�˻����Ȳ�Ϊ�涨��6λʱ,����0
	for (int i = 0; i < length; i++)
	{
		if (acc[i]<'0' || acc[i]>'9')
		{
			return 1;
		}
	}//�˻���Ϊ������ʱ������1
	return 2;//�˻��Ϸ�������2
}


/**********************************************************
[������] fwrite_account
[�������1] ��Ӧ���˻���ָ��
[�������2] ��Ӧ���ļ�ָ��
[����ֵ] ���ȷǷ�����0,�˻���Ϊ������ʱ������1,//�˻��Ϸ�������2
[��������] ��һ���˻�����Ϣд���ļ��б���
[���÷ǿ⺯��] encryption
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"safe.h"
***********************************************************/
void fwrite_account(Account* account, FILE* fp)
{	
	encryption(account->str_acc);//�����˻�
	encryption(account->str_password);//��������
	fputc('!',fp);//д��ʱ��д��һ�������ַ���ʹ���ж��ļ�β��ʱʹ��fgetc�������Ӱ��
	fprintf(fp, "%s", account->str_acc);//����˻����ļ���ĩβ����ӻس�
	fprintf(fp, "%s\n", account->str_password);//����˻����뵽�ļ���ĩβ��ӻس�
}

/****************************************************
[������] fread_account
[�������] ��
[����ֵ] �˻�����ָ��
[��������] ���˻���Ϣ��ȡΪ����ṹ�����������˻�
[���÷ǿ⺯��] decrption
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"safe.h"
*****************************************************/
Account* fread_account()
{
	FILE *fp = fopen("account.log", "r");//�˻��ļ���
	if (fp == NULL)//�ļ�������ʱ�½��ļ�
	{
		fp = fopen("account.log", "w");
		printf("�˻��ļ������ڣ��Ѿ����´���\n");
		return NULL;
	}
	if (fp == NULL)//�ļ���ȡʧ��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n");
		return NULL;
	}
	Account *head=(Account*)malloc(sizeof(Account));
	head->next = NULL;
	Account *p=head;//βָ��p,ָ�����һ���ڵ�
	while (fgetc(fp)!=EOF)
	{
		Account* newacc = (Account*)malloc(sizeof(Account));//�����µĽڵ�
		fgets(newacc->str_acc, 7, fp);
		fgets(newacc->str_password, 17, fp);//��ȡ�ļ�������һ���˻�����Ϣ��
		newacc->str_password[strlen(newacc->str_password)-1] = '\0';//ȥ�����ȡ���ַ�
		decrption(newacc->str_acc);
		decrption(newacc->str_password);//���ļ���Ϣ���н���
		newacc->next = NULL;
		p->next = newacc;//���µ���Ϣ���뵽����β��
		p = p->next;//����βָ��p
	}
	p = head;
	head = head->next;
	free(p);//�ͷŵ���ͷ�ı�־�ڵ�
	fclose(fp);
	return head;//��������ͷָ�룬������־�ڵ�
}

/*************************************
[������] loc_account
[�������1] �û���
[�������2] ���ص����˻�������ָ��
[����ֵ] �˻�����ָ��
[��������] �����û������������ص��˻�ָ��
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
**************************************/
Account* loc_account(char a[], Account* account)
{
	Account *p = account;
	while (p!=NULL)
	{
		if (strcmp(a, p->str_acc) == 0)
		{
			return p;
		}
		else
		{
			p = p->next;
		}
	}
	return NULL;
}

/*********************************
[������] free_accountlist
[�������] �˻�����ָ��
[����ֵ] ��
[��������] �ͷ��˻�����
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
**********************************/
void free_accountlist(Account* accountlist)
{
	Account *p = accountlist;
	while (p != NULL)
	{	
		accountlist = accountlist->next;
		free(p);
		p = accountlist;
	}
}

/***********************************
[������] show_account
[�������] �˻�����ָ��
[����ֵ] ��
[��������] ��ʾ�����˻�
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
*************************************/
void show_account()
{
	printf("�����˻����£�\n");
	Account *accountlist = fread_account();
	Account *p = accountlist;
	while (p != NULL)
	{	
		accountlist = accountlist->next;
		printf("%s\n", p->str_acc);
		free(p);
		p = accountlist;
	}
	printf("\n\n\n\n\n");
}