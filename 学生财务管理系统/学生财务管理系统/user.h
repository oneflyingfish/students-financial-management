#ifndef USER_H
#define USER_H
#pragma warning(disable:4996)//屏蔽VS2017根据新的标准，对fopen等函数的不安全考虑，造成的警告
#include<stdio.h>


/*******************************
[结构体名] User
[成员1] STU_ID[12]	//用户学号
[成员2] phone[12]	//用户电话
[成员3] overage		//用户余额
[成员4]	name[12]	//用户姓名
[成员5] next		//User指针
********************************/
typedef struct User
{
	char STU_ID[12];//用户学号
	char phone[12];
	double overage;//用户余额
	char name[12];//用户姓名（由于是汉字，故空间略大）			
	struct User *next;//链接到收费记录
}User;


/*************************************************************************
[函数名] add_user
[传入参数] 无
[返回值] 无
[函数功能] 添加新用户
[调用非库函数] fwrite_user;loc_user;fwrite_user;fread_users;free_userlist
[头文件的使用] <stdio.h>;<string.h>;"log.h"
****************************************************************************/
void add_user();//添加新用户

/***********************************************************
[函数名] delete_user
[传入参数] 无
[返回值] 无
[函数功能] 注销用户
[调用非库函数] fread_users;loc_user;fwrite_user;free_userlist
[头文件的使用] <stdio.h>;<string.h>;
*************************************************************/
void delete_user();//注销用户

/*******************************************
[函数名] fread_users
[传入参数] 无
[返回值] 用户类型指针
[函数功能] 将用户信息读取为链表结构，加载所有用户
[调用非库函数] decrption;fwrite_user
[头文件的使用] <stdio.h>;<string.h>;"safe.h";
*********************************************/
User* fread_users();//将用户信息读取为链表结构，加载所有用户

/*********************************************
[函数名] fwrite_user
[传入参数1] 相应的用户结构体的指针
[传入参数2] 相应的文件指针
[返回值] 无
[函数功能] 将一个用户的信息写入文件中保存
[调用非库函数] decrption
[头文件的使用] <stdio.h>;<string.h>;"safe.h";
**********************************************/
void fwrite_user(User*, FILE*);//将一个用户的信息写入文件中保存

/***************************************
[函数名] loc_user
[传入参数1] 学号或者姓名
[传入参数2] 加载到的用户链表首指针
[返回值] 用户类型指针
[函数功能] 根据用户名搜索到加载的用户指针
[调用非库函数] 无
[头文件的使用] <stdio.h>;<string.h>
******************************************/
User* loc_user(char a[], User*);//根据用户名搜索到加载的用户指针

/*********************************
[函数名] free_userlist
[传入参数] 加载到的用户链表首指针
[返回值] 无
[函数功能] 释放链表空间
[调用非库函数] 无
[头文件的使用] <stdio.h>
**********************************/
void free_userlist(User* userlist);//释放链表空间

/*********************************
[函数名] show_user
[传入参数] 无
[返回值] 无
[函数功能] [函数功能]显示所有用户信息
[调用非库函数] fread_users
[头文件的使用] <stdio.h>
**********************************/
void show_user();//显示所有用户信息

/*********************************
[函数名] fwrite_user_list
[传入参数] 用户链表
[返回值] 无
[函数功能] 将链表写入文件
[调用非库函数] fwrite_user
[头文件的使用] <stdio.h>
**********************************/
void fwrite_user_list(User*);//将链表写入文件

#endif