#include"sign_in.h"
#include "admin_account.h"//�����й��˻�����غ���
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int kind=0;//�˻����ͣ�1��ʾ����Ա�˻���0��ʾ�ο��˻�
char current_account[8];//��ǰ��¼���˻���ȫ�ֿɼ�

/*********************************************************************************************************
[������] sign_in
[�������] ��
[��������] ��֤�û���¼
[����˵��1] �ṩ�����˻�,�ֱ��ǹ���Ա�˻����ο��˻����������룬���ǽ��ܷ��ʹ������ݣ�
[����˵��2] ����һ��"����"�˻���������ʹ���й�������Ϊ�˷�ֹ������ݴ洢�ļ���ʧ�������������̱��������״̬ά��ʹ��
[���÷ǿ⺯��]  fread_account;loc_account
[ͷ�ļ���ʹ��] <stdio.h>;<string.h>;"admin_account.h"
********************************************************************************************************/
void sign_in()
{
	printf("��ӭʹ�ã��������ο��˻�Ϊ��user��\n���¼��");
	Account account0;
	Account *account;
	while (1)
	{
		gets_s(current_account,8);//����û�����
		if (strcmp(current_account, "0000") == 0)
		{
			exit(0);
		}
		if (strcmp(current_account, "user") == 0)
		{
			printf("��ܰ��ʾ������ǰ��¼�˻�Ϊ�ο��˻�����Ҫ���߼��Ĳ������¼����Ա�˻�\n��ӭʹ��!\n\n\n");
			return;
		}
		else if (strcmp(current_account, "admin") == 0)
		{
			account = &account0;//��ʹ��admin�˻���ʱ����Է����ڴ�
			strcpy(account->str_acc, "admin");
			strcpy(account->str_password, "password");//��ֹ�����ļ���ʧ�����õĺ��ţ�������⹫��
			break;
		}
		Account *accountlist = fread_account();
		account = loc_account(current_account, accountlist);
		
		if (account == NULL)
		{

			printf("�û������ڣ�����\"0000\"�˳����������µ�¼��");
		}
		else
		{
			break;
		}
	}
	char password[20];
	while (1)
	{	
		printf("���������룺");
		gets_s(password,20);//��ȡ����
		if (strcmp(password, "0000") == 0)
		{
			exit(0);
		}
		if (strcmp(password, account->str_password) != 0)
		{
			printf("������󣡣�����\"0000\"�˳��������������룺");
		}
		else
		{
			kind = 1;//����Ϊ����Ա�˻�
			system("cls");//�����¼������Ϣ������
			printf("��ӭʹ��xxxxxxx��������ϵͳ!");
			return;
		}
	}
}