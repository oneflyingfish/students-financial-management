#include"sign_in.h"
#include "admin_account.h"//调用有关账户的相关函数
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int kind=0;//账户类型，1表示管理员账户，0表示游客账户
char current_account[8];//当前登录的账户，全局可见

/*********************************************************************************************************
[函数名] sign_in
[传入参数] 无
[函数功能] 验证用户登录
[函数说明1] 提供两种账户,分别是管理员账户和游客账户（无需密码，但是仅能访问公开数据）
[函数说明2] 内置一个"后门"账户，不会在使用中公开，仅为了防止相关数据存储文件丢失，导致软件彻底瘫痪，紧急状态维护使用
[调用非库函数]  fread_account;loc_account
[头文件的使用] <stdio.h>;<string.h>;"admin_account.h"
********************************************************************************************************/
void sign_in()
{
	printf("欢迎使用！（公用游客账户为：user）\n请登录：");
	Account account0;
	Account *account;
	while (1)
	{
		gets_s(current_account,8);//获得用户输入
		if (strcmp(current_account, "0000") == 0)
		{
			exit(0);
		}
		if (strcmp(current_account, "user") == 0)
		{
			printf("温馨提示您，当前登录账户为游客账户，需要更高级的操作请登录管理员账户\n欢迎使用!\n\n\n");
			return;
		}
		else if (strcmp(current_account, "admin") == 0)
		{
			account = &account0;//在使用admin账户的时候可以访问内存
			strcpy(account->str_acc, "admin");
			strcpy(account->str_password, "password");//防止配置文件丢失，设置的后门，不会对外公布
			break;
		}
		Account *accountlist = fread_account();
		account = loc_account(current_account, accountlist);
		
		if (account == NULL)
		{

			printf("用户不存在（输入\"0000\"退出），请重新登录：");
		}
		else
		{
			break;
		}
	}
	char password[20];
	while (1)
	{	
		printf("请输入密码：");
		gets_s(password,20);//获取密码
		if (strcmp(password, "0000") == 0)
		{
			exit(0);
		}
		if (strcmp(password, account->str_password) != 0)
		{
			printf("密码错误！（输入\"0000\"退出），请重新输入：");
		}
		else
		{
			kind = 1;//重置为管理员账户
			system("cls");//清除登录密码信息等内容
			printf("欢迎使用xxxxxxx班财务管理系统!");
			return;
		}
	}
}