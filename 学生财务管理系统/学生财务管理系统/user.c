#include "user.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "safe.h"
#pragma warning(disable:4013)//屏蔽VS2017对gets的不安全警告
User standard;

/*************************************************************************
[函数名] add_user
[传入参数] 无
[返回值] 无
[函数功能] 添加新用户
[调用非库函数] fwrite_user;loc_user;fwrite_user;fread_users;free_userlist
[头文件的使用] <stdio.h>;<string.h>;"log.h"
****************************************************************************/
void add_user()
{
	FILE *fp = fopen("Users.log", "a");//账户文件追加
	if (fp == NULL)//文件不存在时新建文件
	{
		fp = fopen("Users.log", "w");
		printf("用户信息文件不存在，已经重新创建（原有信息将丢失）\n");
		User user;
		strcpy(user.STU_ID, "16180288000");
		strcpy(user.name, "卓越班");
		strcpy(user.phone, "           ");
		user.overage = 0;
		fwrite_user(&user, fp);
		fclose(fp);
		fp = fopen("Users.log", "a");
	}
	if (fp == NULL)//文件读取失败
	{
		printf("未知错误!,账户文件打开失败\n");
		return;
	}
	User* userlist = fread_users();
	User user;
	char a[20],p[20];
	printf("请输入添加用户的学号：");
	while (1)
	{
		gets(a);
		if (strcmp(a, "0000") == 0)//用户放弃输入账户，提前退出
		{
			return;
		}
		if (strlen(a) != 11)
		{
			printf("您输入的学号不是11位数（输入\"0000\"退出，请重新输入：");
		}	
		else if (loc_user(a, userlist) != NULL)
		{
			printf("您所添加的用户已存在，即将退出操作！\n\n\n\n\n");
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
	printf("请输入预留用户的手机号（输入0跳过）：");
	while (1)
	{
		gets(p);
		if (strcmp(a, "0000") == 0)//用户放弃输入密码，提前退出
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
			printf("您输入的号码不是11位数（放弃请输入\"0000\"退出)，请重新输入：");
		}
		else
		{
			break;
		}
	}
	strcpy(user.phone, p);
	printf("请输入添加用户的姓名：");
	scanf("%s", user.name);
	printf("请输入添加用户的余额：");
	scanf("%lf", &user.overage);
	fwrite_user(&user, fp);
	free_userlist(userlist);
	fclose(fp);
	printf("添加成功！\n\n\n\n\n\n");
}

/***********************************************************
[函数名] delete_user
[传入参数] 无
[返回值] 无
[函数功能] 注销用户
[调用非库函数] fread_users;loc_user;fwrite_user;free_userlist
[头文件的使用] <stdio.h>;<string.h>;
*************************************************************/
void delete_user()
{
	User* userlist = fread_users();
	User *p = userlist,*q;
	char a[20];//防止用户多输入，造成溢出，故数组略大
	printf("请输入要注销的用户的学号或者姓名：");
	gets(a);//获取用户输入
	q = loc_user(a, userlist);
	if ( q== NULL)//删除的用户不存在
	{
		printf("您输入的用户不存在，为了您的账户安全，即将退出操作！\n\n");
		return;
	}
	else if(strcmp(a,"161802880000")==0|| strcmp(a, "卓越班")==0)
	{
		printf("此账户为内置标准账户，不得删除，即将退出操作\n\n");
		return;
	}
	else//链表第一个节点一定是16180288000,故不用考虑头结点
	{
		while (p ->next!= NULL)
		{
			if (strcmp(a, p->next->name) == 0 || strcmp(a, p->next->STU_ID) == 0)//配对成功
			{
				p->next = p->next->next;
				free(q);//删除当前的节点
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
	free_userlist(userlist);//重新写入
	fclose(fp);
	printf("删除成功\n\n\n\n\n\n");
}

/*******************************************
[函数名] fread_users
[传入参数] 无
[返回值] 用户类型指针
[函数功能] 将用户信息读取为链表结构，加载所有用户
[调用非库函数] decrption;fwrite_user
[头文件的使用] <stdio.h>;<string.h>;"safe.h";
*********************************************/
User* fread_users()//读取所有账户，并在堆区用链表方式存储，返回链表头指针
{
	FILE *fp = fopen("Users.log", "r");//账户文件读写
	if (fp == NULL)//文件不存在时新建文件
	{
		printf("用户信息文件被删除移动或不存在，将丢失原来的所有信息，已经为您重新创建\n");
		fp = fopen("Users.log", "w");
		printf("用户信息文件被意外删除，已经重新创建（原有信息将丢失）\n");
		User *user = (User*)malloc(sizeof(User));
		strcpy(user->STU_ID, "16180288000");
		strcpy(user->name, "卓越班");
		strcpy(user->phone, "           ");
		user->overage = 0;
		user->next = NULL;
		fwrite_user(user, fp);
		fclose(fp);
		fp = fopen("Users.log", "r");
	}
	if (fp == NULL)//文件读取失败
	{
		printf("未知错误!,账户文件打开失败\n");
		return NULL;
	}
	User *head = (User*)malloc(sizeof(User));
	head->next = NULL;
	User *p = head;//尾指针p,指向最后一个节点
	while (fgetc(fp) != EOF)
	{
		User* newuser = (User*)malloc(sizeof(User));//创建新的节点
		fgets(newuser->STU_ID, 12, fp);//学号
		fgets(newuser->phone, 12, fp);//电话号码
		fscanf(fp, "%lf", &newuser->overage);//余额
		fgets(newuser->name, 12, fp);//姓名
		newuser->name[strlen(newuser->name) - 1] = '\0';//去掉多读取的字符
		decrption(newuser->name);
		decrption(newuser->phone);
		decrption(newuser->STU_ID);//对文件信息进行解析
		newuser->next = NULL;
		p->next = newuser;//将新的信息加入到链表尾部
		p = p->next;//更新尾指针p
	}
	p = head;
	head = head->next;
	free(p);//释放掉表头的标志节点
	fclose(fp);
	if (head==NULL||strcmp(head->STU_ID, "16180288000") != 0 || strcmp(head->name, "卓越班") != 0|| strcmp(head->phone, "           ") != 0)
	{
		printf("用户信息文件被恶意篡改，将丢失原来的所有信息，已经为您重新创建\n");
		fp = fopen("Users.log", "w+");
		printf("用户信息文件被意外删除，已经重新创建（原有信息将丢失）\n");
		User *user=(User*)malloc(sizeof(User));
		strcpy(user->STU_ID, "16180288000");
		strcpy(user->name, "卓越班");
		strcpy(user->phone, "           ");
		user->overage = 0;
		user->next = NULL;
		fwrite_user(user, fp);
		fclose(fp);
		return user;
	}
	return head;//返回链表头指针，不含标志节点
}

/*********************************************
[函数名] fwrite_user
[传入参数1] 相应的用户结构体的指针
[传入参数2] 相应的文件指针
[返回值] 无
[函数功能] 将一个用户的信息写入文件中保存
[调用非库函数] decrption
[头文件的使用] <stdio.h>;<string.h>;"safe.h";
**********************************************/
void fwrite_user(User* user, FILE* fp)
{
	encryption(user->STU_ID);//加密学号
	encryption(user->phone);//加密电话
	encryption(user->name);//加密姓名
	fputc('!', fp);//写入时多写入一个无用字符，使得判断文件尾部时使用fgetc不会产生影响
	fprintf(fp, "%s",user->STU_ID);//添加学号到文件，末尾不添加回车。多一个空格
	fprintf(fp, "%s", user->phone);//添加电话
	fprintf(fp, "%f", user->overage);//添加余额到文件
	fprintf(fp, "%s\n", user->name);//添加姓名到文件，末尾添加回车
}

/***************************************
[函数名] loc_user
[传入参数1] 学号或者姓名
[传入参数2] 加载到的用户链表首指针
[返回值] 用户类型指针
[函数功能] 根据用户名搜索到加载的用户指针
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
******************************************/
User* loc_user(char a[], User* userlist)
{
	User *p = userlist;
	while (p != NULL)
	{
		if (strcmp(a, p->name) == 0|| strcmp(a, p->STU_ID) == 0)//配对成功
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
[函数名] free_userlist
[传入参数] 加载到的用户链表首指针
[返回值] 无
[函数功能] 释放链表空间
[调用非库函数] 无
[头文件的使用] <stdio.h>
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
[函数名] show_user
[传入参数] 无
[返回值] 无
[函数功能] [函数功能]显示所有用户信息
[调用非库函数] fread_users
[头文件的使用] <stdio.h>
**********************************/
void show_user()
{
	printf("所有账户如下：\n");
	User *userlist = fread_users();
	User *p = userlist;
	while (p != NULL)
	{
		userlist = userlist->next;
		printf("%-14s", p->STU_ID);
		printf("%-8s    ", p->name);
		printf("余额：%-8.2f  ", p->overage);
		printf("电话：%s\n", p->phone);
		free(p);
		p = userlist;
	}
	printf("\n\n\n\n\n");
}


/*********************************
[函数名] fwrite_user_list
[传入参数] 用户链表
[返回值] 无
[函数功能] 将链表写入文件
[调用非库函数] fwrite_user
[头文件的使用] <stdio.h>
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