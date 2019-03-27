#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "admin_account.h"//使用管理员“账户结构体”以及相关所有功能
#include "sign_in.h"//使用登录功能
#include "menu.h"//使用菜单打印功能
#include "user.h"//使用“用户结构体”以及相关读取，增加，删除等功能
#include "bill.h"
#include "log.h"

extern int kind;

int main()
{
LOOP0://切换登录时使用
	sign_in();
	int choose;
	if (kind == 1)//管理员账户
	{
		admin_menu();
		while (1)
		{
			scanf("%d", &choose);
			getchar();//吸收回车字符
			if (choose == 0)//结束操作
			{
				break;
			}
			switch (choose)
			{
			case 1://账户管理
				admin_account_menu();
				while (1)
				{
					scanf("%d", &choose);
					getchar();//吸收回车字符
					if (choose == 0)//账户管理--退回上一步
					{
						admin_menu();
						break;
					}
					switch (choose)
					{
					case 1://账户管理---添加管理员
						add_account();
						admin_account_menu();
						break;
					case 2://账户管理---删除管理员
						delete_account();
						admin_account_menu();
						break;
					case 3://账户管理---显示所有管理员账户
						show_account();
						admin_account_menu();
						break;
					case 4://账户管理--- 添加用户
						add_user();
						admin_account_menu();
						break;
					case 5://账户管理---删除用户
						delete_user();
						admin_account_menu();
						break;
					case 6://账户管理---显示所有用户信息
						show_user();
						admin_account_menu();
						break;
					case 9://清除屏幕历史查询信息
						system("cls");
						printf("欢迎使用xxxxxxx班财务管理系统");
						admin_account_menu();
						break;
					default://用户输入错误
						printf("\n您输入的代号有误，请重新对照输入菜单\n");
						admin_account_menu();
					}
				}
				break;
			case 2://财务管理
				admin_bill_inform_menu();
				while (1)
				{
					scanf("%d", &choose);
					getchar();//吸收回车字符
					if (choose == 0)//财务管理---退回上一步
					{
						admin_menu();
						break;
					}
					switch (choose)
					{
					case 1://财务管理---收账管理
						admin_income_menu();
						while (1)
						{
							scanf("%d", &choose);
							getchar();//吸收回车字符
							if (choose == 0)//财务管理---收账管理---退回上一步
							{
								admin_bill_inform_menu();
								break;
							}
							switch (choose)
							{
							case 1://财务管理---收账管理---建立收费记录
								setup_log1();
								admin_income_menu();
								break;
							case 2://财务管理---收账管理---单个入账
								incount_inorder();
								admin_income_menu();
								break;
							case 3://财务管理---收账管理---扣除费用
								outcount_inorder();
								admin_income_menu();
								break;
							case 4://账务管理---收账管理---班级集体入账
								incount_inqueue();
								admin_income_menu();
								break;
							case 5://显示费用未收齐用户
								user_arrearage();
								admin_income_menu();
								break;
							case 9://清除屏幕历史查询信息
								system("cls");
								printf("欢迎使用xxxxxxx班财务管理系统");
								admin_income_menu();
								break;
							default:
								printf("\n您输入的代号有误，请重新对照输入菜单\n");
								admin_income_menu();
							}
						}
						break;
					case 2://财务管理---支出管理
						admin_outcome_menu();
						while (1)
						{
							scanf("%d", &choose);
							getchar();//吸收回车字符
							if (choose == 0)//财务管理---支出管理---退回上一步
							{
								admin_outcome_menu();
								admin_outcome_menu();
								break;
							}
							switch (choose)
							{
							case 1://财务管理---支出管理---财务支出
								setup_log2();
								admin_outcome_menu();
								break;
							case 2://财务管理---支出管理---历史费用变动记录
								fprint_log();
								admin_outcome_menu();
								break;
							case 9://清除屏幕历史查询信息
								system("cls");
								printf("欢迎使用xxxxxxx班财务管理系统");
								admin_outcome_menu();
								break;
							default:
								printf("\n您输入的代号有误，请重新对照输入菜单\n");
								admin_outcome_menu();
							}
						}
						break;
					case 3://财务管理---余额不足用户
						arrearage_situation();
						admin_bill_inform_menu();
						break;
					case 4://财务管理---费用欠收情况
						user_arrearage();
						admin_bill_inform_menu();
						break;
					case 5://清除历史记录
						fclear_log();
						admin_bill_inform_menu();
						break;
					case 6://显示历史费用变动记录
						fprint_log();
						admin_bill_inform_menu();
						break;
					case 7://查询某学生余额
						allaccount_administor();
						admin_bill_inform_menu();
						break;
					case 9://清除屏幕历史查询信息
						system("cls");
						printf("欢迎使用xxxxxxx班财务管理系统");
						admin_bill_inform_menu();
						break;
					default:
						printf("\n您输入的代号有误，请重新对照输入菜单\n");
						admin_bill_inform_menu();
					}
				}
				break;
			case 9://清除屏幕历史查询信息
				system("cls");
				printf("欢迎使用xxxxxxx班财务管理系统");
				admin_menu();
				break;
			default://输入错误
				printf("\n您输入的代号有误，请重新对照输入菜单\n");
				admin_menu();
			}
		}
	}
	else//游客账户登录
	{
		user_menu();
		while (1)
		{
			scanf("%d", &choose);
			getchar();//吸收回车字符
			if (choose == 0)//结束操作
			{
				break;
			}
			if (choose == 1)
			{
				goto LOOP0;//切换账户，重新登录
			}
			switch (choose)
			{
			case 2://余额不足用户
				arrearage_situation();
				admin_income_menu();
				break;
			case 3://费用欠收情况
				user_arrearage();
				admin_income_menu();
				break;
			case 4://历史费用变动记录
				fprint_log();
				admin_income_menu();
				break;
			case 9://清除屏幕历史查询信息
				system("cls");
				printf("欢迎使用xxxxxxx班财务管理系统");
				admin_income_menu();
				break;
			default:
				printf("\n您输入的代号有误，请重新对照输入菜单\n");
				admin_income_menu();
			}
		}
	}
	return 0;
}