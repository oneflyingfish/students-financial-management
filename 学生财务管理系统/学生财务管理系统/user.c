#include "user.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "safe.h"
#pragma warning(disable:4013)//����VS2017��gets�Ĳ���ȫ����
User standard;

/*************************************************************************
[������] add_user
[�������] ��
[����ֵ] ��
[��������] ������û�
[���÷ǿ⺯��] fwrite_user;loc_user;fwrite_user;fread_users;free_userlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"log.h"
****************************************************************************/
void add_user()
{
	FILE *fp = fopen("Users.log", "a");//�˻��ļ�׷��
	if (fp == NULL)//�ļ�������ʱ�½��ļ�
	{
		fp = fopen("Users.log", "w");
		printf("�û���Ϣ�ļ������ڣ��Ѿ����´�����ԭ����Ϣ����ʧ��\n");
		User user;
		strcpy(user.STU_ID, "16180288000");
		strcpy(user.name, "׿Խ��");
		strcpy(user.phone, "           ");
		user.overage = 0;
		fwrite_user(&user, fp);
		fclose(fp);
		fp = fopen("Users.log", "a");
	}
	if (fp == NULL)//�ļ���ȡʧ��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n");
		return;
	}
	User* userlist = fread_users();
	User user;
	char a[20],p[20];
	printf("����������û���ѧ�ţ�");
	while (1)
	{
		gets(a);
		if (strcmp(a, "0000") == 0)//�û����������˻�����ǰ�˳�
		{
			return;
		}
		if (strlen(a) != 11)
		{
			printf("�������ѧ�Ų���11λ��������\"0000\"�˳������������룺");
		}	
		else if (loc_user(a, userlist) != NULL)
		{
			printf("������ӵ��û��Ѵ��ڣ������˳�������\n\n\n\n\n");
			free_userlist(userlist);
			fclose(fp);
			return;
		}
		else
		{
			break;
		}
	}
	strcpy(user.STU_ID, a);
	printf("������Ԥ���û����ֻ��ţ�����0��������");
	while (1)
	{
		gets(p);
		if (strcmp(a, "0000") == 0)//�û������������룬��ǰ�˳�
		{
			return;
		}
		if (strcmp(p,"0")==0)
		{
			strcpy(p, "           ");
			break;
		}
		if (strlen(p) != 11)
		{
			printf("������ĺ��벻��11λ��������������\"0000\"�˳�)�����������룺");
		}
		else
		{
			break;
		}
	}
	strcpy(user.phone, p);
	printf("����������û���������");
	scanf("%s", user.name);
	printf("����������û�����");
	scanf("%lf", &user.overage);
	fwrite_user(&user, fp);
	free_userlist(userlist);
	fclose(fp);
	printf("��ӳɹ���\n\n\n\n\n\n");
}

/***********************************************************
[������] delete_user
[�������] ��
[����ֵ] ��
[��������] ע���û�
[���÷ǿ⺯��] fread_users;loc_user;fwrite_user;free_userlist
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;
*************************************************************/
void delete_user()
{
	User* userlist = fread_users();
	User *p = userlist,*q;
	char a[20];//��ֹ�û������룬���������������Դ�
	printf("������Ҫע�����û���ѧ�Ż���������");
	gets(a);//��ȡ�û�����
	q = loc_user(a, userlist);
	if ( q== NULL)//ɾ�����û�������
	{
		printf("��������û������ڣ�Ϊ�������˻���ȫ�������˳�������\n\n");
		return;
	}
	else if(strcmp(a,"161802880000")==0|| strcmp(a, "׿Խ��")==0)
	{
		printf("���˻�Ϊ���ñ�׼�˻�������ɾ���������˳�����\n\n");
		return;
	}
	else//�����һ���ڵ�һ����16180288000,�ʲ��ÿ���ͷ���
	{
		while (p ->next!= NULL)
		{
			if (strcmp(a, p->next->name) == 0 || strcmp(a, p->next->STU_ID) == 0)//��Գɹ�
			{
				p->next = p->next->next;
				free(q);//ɾ����ǰ�Ľڵ�
			}
			else
			{
				p = p->next;
			}
		}
	}
	FILE* fp = fopen("Users.log", "w");
	p =userlist;
	while (p != NULL)
	{
		fwrite_user(p, fp);
		p = p->next;
	}
	free_userlist(userlist);//����д��
	fclose(fp);
	printf("ɾ���ɹ�\n\n\n\n\n\n");
}

/*******************************************
[������] fread_users
[�������] ��
[����ֵ] �û�����ָ��
[��������] ���û���Ϣ��ȡΪ����ṹ�����������û�
[���÷ǿ⺯��] decrption;fwrite_user
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"safe.h";
*********************************************/
User* fread_users()//��ȡ�����˻������ڶ���������ʽ�洢����������ͷָ��
{
	FILE *fp = fopen("Users.log", "r");//�˻��ļ���д
	if (fp == NULL)//�ļ�������ʱ�½��ļ�
	{
		printf("�û���Ϣ�ļ���ɾ���ƶ��򲻴��ڣ�����ʧԭ����������Ϣ���Ѿ�Ϊ�����´���\n");
		fp = fopen("Users.log", "w");
		printf("�û���Ϣ�ļ�������ɾ�����Ѿ����´�����ԭ����Ϣ����ʧ��\n");
		User *user = (User*)malloc(sizeof(User));
		strcpy(user->STU_ID, "16180288000");
		strcpy(user->name, "׿Խ��");
		strcpy(user->phone, "           ");
		user->overage = 0;
		user->next = NULL;
		fwrite_user(user, fp);
		fclose(fp);
		fp = fopen("Users.log", "r");
	}
	if (fp == NULL)//�ļ���ȡʧ��
	{
		printf("δ֪����!,�˻��ļ���ʧ��\n");
		return NULL;
	}
	User *head = (User*)malloc(sizeof(User));
	head->next = NULL;
	User *p = head;//βָ��p,ָ�����һ���ڵ�
	while (fgetc(fp) != EOF)
	{
		User* newuser = (User*)malloc(sizeof(User));//�����µĽڵ�
		fgets(newuser->STU_ID, 12, fp);//ѧ��
		fgets(newuser->phone, 12, fp);//�绰����
		fscanf(fp, "%lf", &newuser->overage);//���
		fgets(newuser->name, 12, fp);//����
		newuser->name[strlen(newuser->name) - 1] = '\0';//ȥ�����ȡ���ַ�
		decrption(newuser->name);
		decrption(newuser->phone);
		decrption(newuser->STU_ID);//���ļ���Ϣ���н���
		newuser->next = NULL;
		p->next = newuser;//���µ���Ϣ���뵽����β��
		p = p->next;//����βָ��p
	}
	p = head;
	head = head->next;
	free(p);//�ͷŵ���ͷ�ı�־�ڵ�
	fclose(fp);
	if (head==NULL||strcmp(head->STU_ID, "16180288000") != 0 || strcmp(head->name, "׿Խ��") != 0|| strcmp(head->phone, "           ") != 0)
	{
		printf("�û���Ϣ�ļ�������۸ģ�����ʧԭ����������Ϣ���Ѿ�Ϊ�����´���\n");
		fp = fopen("Users.log", "w+");
		printf("�û���Ϣ�ļ�������ɾ�����Ѿ����´�����ԭ����Ϣ����ʧ��\n");
		User *user=(User*)malloc(sizeof(User));
		strcpy(user->STU_ID, "16180288000");
		strcpy(user->name, "׿Խ��");
		strcpy(user->phone, "           ");
		user->overage = 0;
		user->next = NULL;
		fwrite_user(user, fp);
		fclose(fp);
		return user;
	}
	return head;//��������ͷָ�룬������־�ڵ�
}

/*********************************************
[������] fwrite_user
[�������1] ��Ӧ���û��ṹ���ָ��
[�������2] ��Ӧ���ļ�ָ��
[����ֵ] ��
[��������] ��һ���û�����Ϣд���ļ��б���
[���÷ǿ⺯��] decrption
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"safe.h";
**********************************************/
void fwrite_user(User* user, FILE* fp)
{
	encryption(user->STU_ID);//����ѧ��
	encryption(user->phone);//���ܵ绰
	encryption(user->name);//��������
	fputc('!', fp);//д��ʱ��д��һ�������ַ���ʹ���ж��ļ�β��ʱʹ��fgetc�������Ӱ��
	fprintf(fp, "%s",user->STU_ID);//���ѧ�ŵ��ļ���ĩβ����ӻس�����һ���ո�
	fprintf(fp, "%s", user->phone);//��ӵ绰
	fprintf(fp, "%f", user->overage);//������ļ�
	fprintf(fp, "%s\n", user->name);//����������ļ���ĩβ��ӻس�
}

/***************************************
[������] loc_user
[�������1] ѧ�Ż�������
[�������2] ���ص����û�������ָ��
[����ֵ] �û�����ָ��
[��������] �����û������������ص��û�ָ��
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>
******************************************/
User* loc_user(char a[], User* userlist)
{
	User *p = userlist;
	while (p != NULL)
	{
		if (strcmp(a, p->name) == 0|| strcmp(a, p->STU_ID) == 0)//��Գɹ�
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
[������] free_userlist
[�������] ���ص����û�������ָ��
[����ֵ] ��
[��������] �ͷ�����ռ�
[���÷ǿ⺯��] ��
[ͷ�ļ���ʹ��] <stdio.h>
**********************************/
void free_userlist(User* userlist)
{
	User *p = userlist;
	while (p != NULL)
	{
		userlist = userlist->next;
		free(p);
		p = userlist;
	}
}

/*********************************
[������] show_user
[�������] ��
[����ֵ] ��
[��������] [��������]��ʾ�����û���Ϣ
[���÷ǿ⺯��] fread_users
[ͷ�ļ���ʹ��] <stdio.h>
**********************************/
void show_user()
{
	printf("�����˻����£�\n");
	User *userlist = fread_users();
	User *p = userlist;
	while (p != NULL)
	{
		userlist = userlist->next;
		printf("%-14s", p->STU_ID);
		printf("%-8s    ", p->name);
		printf("��%-8.2f  ", p->overage);
		printf("�绰��%s\n", p->phone);
		free(p);
		p = userlist;
	}
	printf("\n\n\n\n\n");
}


/*********************************
[������] fwrite_user_list
[�������] �û�����
[����ֵ] ��
[��������] ������д���ļ�
[���÷ǿ⺯��] fwrite_user
[ͷ�ļ���ʹ��] <stdio.h>
**********************************/
void fwrite_user_list(User *userlist)
{
	User* p = userlist;
	FILE *fp = fopen("Users.log", "w");
	while (p != NULL)
	{
		fwrite_user(p, fp);
		p = p->next;
	}
	fclose(fp);
}