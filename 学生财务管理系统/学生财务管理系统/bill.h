#ifndef BILL_H
#define BILL_H
/********************
[函数名]incount_inorder
[传入参数] 无
[返回值] 无
[函数功能]对某一个学生进行单独入账
[调用非库函数] fread_users,loc_user,fwrite_user_list;free_userlist;
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void incount_inorder();

/********************
[函数名]outcount_inorder
[传入参数] 无
[返回值] 无
[函数功能]对某一个学生进行单独出账
[调用非库函数] fread_users,loc_user,fwrite_user_list;free_userlist;
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void outcount_inorder();

/*************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能] 集体入账，所有除对照用户外的用户同时存入或输出一个金额
[调用非库函数] fread_users,free_userlist，fwrite_user_list
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void incount_inqueue();

/*************************************
[函数名]user_arrearage
[传入参数] 无
[返回值] 无
[函数功能]未交费用户的名字和用户所差金额
[调用非库函数] fread_users,free_userlist
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void user_arrearage();//费用欠收情况


/*************************************
[函数名]allaccount_administor
[传入参数] 无
[返回值] 无
[函数功能]根据学号或姓名查询余额
[调用非库函数] fread_users,free_userlist,loc_user
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void allaccount_administor();//根据学号或者姓名获取余额

/*************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能]欠费学生的姓名，电话输出
[调用非库函数] fread_users,free_userlist,loc_user
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void arrearage_situation();

/*************************************
[函数名]arrearage_situation
[传入参数] 无
[返回值] 无
[函数功能]显示班级班费总余额
[调用非库函数] fread_users,free_userlist
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void allaccount_visitor();

/*************************************
[函数名]arrearage_situation
[传入参数] float型参变量
[返回值] 无
[函数功能] 集体出账，班费的支出由所有人共同承担
[调用非库函数] fread_users,free_userlist，fwrite_user_list
[头文件的使用] <stdio.h>;<string.h>;"User.h";
******************************************************************************************/
void outaccount_inqueue(float);

/*************************************
[函数名]setup_log1
[传入参数] 无
[返回值] 无
[函数功能] 建立入账日志
[调用非库函数] fread_users,free_userlist，fwrite_user_list,get_time,fread_log,fwrite_log,free_loglist
[头文件的使用] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log1();//建立入账日志

/*************************************
[函数名]setup_log1
[传入参数] 无
[返回值] 无
[函数功能] 建立入账日志
[调用非库函数] fread_users,free_userlist,get_time,fread_log,fwrite_log,free_loglist
[头文件的使用] <stdio.h>;<string.h>;"User.h";"log.h""gettime.h"
******************************************************************************************/
void setup_log2();//建立支出日志


#endif