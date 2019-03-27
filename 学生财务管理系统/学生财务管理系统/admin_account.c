#include "admin_account.h"
#include "safe.h"
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4013)//屏蔽VS2017对gets的不安全警告
#pragma warning(disable:4267)//屏蔽VS2017对strlen返回值的警告
extern char current_account[8];


/***************************************************************************************
[函数名] add_account
[传入参数] 无
[返回值] 无
[函数功能] 添加新账户
[调用非库函数] fread_account;judge_acclegal;loc_account;fwrite_account;free_accountlist
[头文件的使用] <stdio.h>;<string.h>;"safe.h"
******************************************************************************************/
void add_account()
{
	Account *account=(Account*)malloc(sizeof(Account));
	account->next = NULL;
	Account *accountlist = fread_account();//加载已有账户
	printf("请输入账户名(六位纯数字组成）：");
	char acc[10];//数组略大于实际使用，防止用户输入过多造成错误
	char password1[30];//数组略大于实际使用，防止用户输入过多造成错误(下同）
	char password2[30];
	while (1)//获得账户
	{
		gets(acc);//获得用户输入的账户
		if (strcmp(acc, "0000") == 0)//用户放弃创建账户，提前退出
		{
			return;
		}
		if (judge_acclegal(acc) == 0)//输入的账户长度非法
		{
			printf("您输入的账户不是六位，请重新输入：");
			continue;
		}
		else if (judge_acclegal(acc) == 1)//账户不为纯数字非法
		{
			printf("您输入的账户包含非数字字符，请重新输入：");
			continue;
		}
		else if (loc_account(acc, accountlist) != NULL)//用户名已经注册
		{
			printf("您输入的账户已经存在（退出请输入\"0000\")，请重新输入：");
			continue;
		}
		else//账户合法
		{
			break;
		}
	}
	LOOP0://重新设置密码
	printf("请设置8-16位密码：");
	while (1)//初次获得密码
	{
		gets(password1);//输入密码
		if (strlen(password1) > 16 || strlen(password1) < 8)//密码位数非法
		{
			printf("您输入的密码位数不在8~16位，请重新输入您的密码：");
			continue;
		}
		else//首次输入密码合法
		{
			break;
		}
	}
	system("cls");
	printf("请再次输入密码：");
	while (1)//确认密码
	{
		gets(password2);//获得确认的密码
		if (strcmp(password2, "0000") == 0)//用户选择重新输入密码
		{
			goto LOOP0;
		}
		else if (strcmp(password1, password2)!=0)//两次输入密码不相同
		{
			printf("您两次输入的密码不完全相同(如果您想重新设置密码，请输入\"0000\")，请再次确认您的密码:");
			continue;
		}
		else//确认密码成功
		{
			break;
		}
	}
	strcpy(account->str_acc, acc);
	strcpy(account->str_password, password1);

	FILE*fp = fopen("account.log", "a");
	if (fp == NULL)//文件不存在，且新建时发生错误
	{
		printf("未知错误!,账户文件打开失败\n");
		return;
	}
	fwrite_account(account, fp);//追加新的账户
	fclose(fp);
	free(account);
	free_accountlist(accountlist);
	system("cls");
	printf("操作完成\n\n\n\n\n\n");
}

/**************************************************************************
[函数名] delete_account
[传入参数] 无
[返回值] 无
[函数功能] 删除已有账户
[调用非库函数] fread_account;loc_account;fwrite_account;free_accountlist
[头文件的使用] <stdio.h>;<string.h>
**************************************************************************/
void delete_account()//删除账户
{

	Account *accountlist = fread_account();
	printf("请输入您想要删除的用户名：");
	char acc[10];//数组略大于实际使用，防止用户输入过多造成错误
	char password[30];//数组略大于实际使用，防止用户输入过多造成错误
	gets(acc);
	if (strcmp(acc, current_account) == 0)
	{
		printf("不能删除当前账户\n");
		return;
	}
	Account *loc = loc_account(acc, accountlist), *q;//获得想要删除的账户结构体
	if (loc == NULL)
	{
		printf("用户不存在！即将退出操作！\n");
		return;
	}
	printf("请输入密码：");
	gets(password);
	if (strcmp(loc->str_password, password) == 0)//密码确认正确，进行删除操作
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
		printf("删除成功！\n\n\n\n\n\n");
	}
	else
	{
		printf("密码错误，为了您的账户安全，即将退出操作\n\n\n\n\n");
		return;
	}
	FILE *fp = fopen("account.log", "w");//账户文件读写
	if (fp == NULL)//账户文件不存在，创建新的文件写入
	{
		printf("未知错误!,账户文件打开失败\n");
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
[函数名] judge_acclegal
[传入参数] 需要判断的字符串
[返回值] 长度非法返回0,账户不为纯数字时，返回1,//账户合法，返回2
[函数功能] 判断用户名是否符合标准
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
*********************************************************/
int judge_acclegal(char acc[])
{
	int length = strlen(acc);//获得得到的账户的长度
	if (length != 6)
	{
		return 0;
	}//账户长度不为规定的6位时,返回0
	for (int i = 0; i < length; i++)
	{
		if (acc[i]<'0' || acc[i]>'9')
		{
			return 1;
		}
	}//账户不为纯数字时，返回1
	return 2;//账户合法，返回2
}


/**********************************************************
[函数名] fwrite_account
[传入参数1] 相应的账户的指针
[传入参数2] 相应的文件指针
[返回值] 长度非法返回0,账户不为纯数字时，返回1,//账户合法，返回2
[函数功能] 将一个账户的信息写入文件中保存
[调用非库函数] encryption
[头文件的使用] <stdio.h>;<string.h>;"safe.h"
***********************************************************/
void fwrite_account(Account* account, FILE* fp)
{	
	encryption(account->str_acc);//加密账户
	encryption(account->str_password);//加密密码
	fputc('!',fp);//写入时多写入一个无用字符，使得判断文件尾部时使用fgetc不会产生影响
	fprintf(fp, "%s", account->str_acc);//添加账户到文件，末尾不添加回车
	fprintf(fp, "%s\n", account->str_password);//添加账户密码到文件，末尾添加回车
}

/****************************************************
[函数名] fread_account
[传入参数] 无
[返回值] 账户类型指针
[函数功能] 将账户信息读取为链表结构，加载所有账户
[调用非库函数] decrption
[头文件的使用] <stdio.h>;<string.h>;"safe.h"
*****************************************************/
Account* fread_account()
{
	FILE *fp = fopen("account.log", "r");//账户文件读
	if (fp == NULL)//文件不存在时新建文件
	{
		fp = fopen("account.log", "w");
		printf("账户文件不存在，已经重新创建\n");
		return NULL;
	}
	if (fp == NULL)//文件读取失败
	{
		printf("未知错误!,账户文件打开失败\n");
		return NULL;
	}
	Account *head=(Account*)malloc(sizeof(Account));
	head->next = NULL;
	Account *p=head;//尾指针p,指向最后一个节点
	while (fgetc(fp)!=EOF)
	{
		Account* newacc = (Account*)malloc(sizeof(Account));//创建新的节点
		fgets(newacc->str_acc, 7, fp);
		fgets(newacc->str_password, 17, fp);//读取文件流中下一个账户的信息，
		newacc->str_password[strlen(newacc->str_password)-1] = '\0';//去掉多读取的字符
		decrption(newacc->str_acc);
		decrption(newacc->str_password);//对文件信息进行解析
		newacc->next = NULL;
		p->next = newacc;//将新的信息加入到链表尾部
		p = p->next;//更新尾指针p
	}
	p = head;
	head = head->next;
	free(p);//释放掉表头的标志节点
	fclose(fp);
	return head;//返回链表头指针，不含标志节点
}

/*************************************
[函数名] loc_account
[传入参数1] 用户名
[传入参数2] 加载到的账户链表首指针
[返回值] 账户类型指针
[函数功能] 根据用户名搜索到加载的账户指针
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
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
[函数名] free_accountlist
[传入参数] 账户类型指针
[返回值] 无
[函数功能] 释放账户链表
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
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
[函数名] show_account
[传入参数] 账户类型指针
[返回值] 无
[函数功能] 显示所有账户
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
*************************************/
void show_account()
{
	printf("所有账户如下：\n");
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