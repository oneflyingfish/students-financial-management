#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "admin_account.h"//ʹ�ù���Ա���˻��ṹ�塱�Լ�������й���
#include "sign_in.h"//ʹ�õ�¼����
#include "menu.h"//ʹ�ò˵���ӡ����
#include "user.h"//ʹ�á��û��ṹ�塱�Լ���ض�ȡ�����ӣ�ɾ���ȹ���
#include "bill.h"
#include "log.h"

extern int kind;

int main()
{
LOOP0://�л���¼ʱʹ��
	sign_in();
	int choose;
	if (kind == 1)//����Ա�˻�
	{
		admin_menu();
		while (1)
		{
			scanf("%d", &choose);
			getchar();//���ջس��ַ�
			if (choose == 0)//��������
			{
				break;
			}
			switch (choose)
			{
			case 1://�˻�����
				admin_account_menu();
				while (1)
				{
					scanf("%d", &choose);
					getchar();//���ջس��ַ�
					if (choose == 0)//�˻�����--�˻���һ��
					{
						admin_menu();
						break;
					}
					switch (choose)
					{
					case 1://�˻�����---��ӹ���Ա
						add_account();
						admin_account_menu();
						break;
					case 2://�˻�����---ɾ������Ա
						delete_account();
						admin_account_menu();
						break;
					case 3://�˻�����---��ʾ���й���Ա�˻�
						show_account();
						admin_account_menu();
						break;
					case 4://�˻�����--- ����û�
						add_user();
						admin_account_menu();
						break;
					case 5://�˻�����---ɾ���û�
						delete_user();
						admin_account_menu();
						break;
					case 6://�˻�����---��ʾ�����û���Ϣ
						show_user();
						admin_account_menu();
						break;
					case 9://�����Ļ��ʷ��ѯ��Ϣ
						system("cls");
						printf("��ӭʹ��xxxxxxx��������ϵͳ");
						admin_account_menu();
						break;
					default://�û��������
						printf("\n������Ĵ������������¶�������˵�\n");
						admin_account_menu();
					}
				}
				break;
			case 2://�������
				admin_bill_inform_menu();
				while (1)
				{
					scanf("%d", &choose);
					getchar();//���ջس��ַ�
					if (choose == 0)//�������---�˻���һ��
					{
						admin_menu();
						break;
					}
					switch (choose)
					{
					case 1://�������---���˹���
						admin_income_menu();
						while (1)
						{
							scanf("%d", &choose);
							getchar();//���ջس��ַ�
							if (choose == 0)//�������---���˹���---�˻���һ��
							{
								admin_bill_inform_menu();
								break;
							}
							switch (choose)
							{
							case 1://�������---���˹���---�����շѼ�¼
								setup_log1();
								admin_income_menu();
								break;
							case 2://�������---���˹���---��������
								incount_inorder();
								admin_income_menu();
								break;
							case 3://�������---���˹���---�۳�����
								outcount_inorder();
								admin_income_menu();
								break;
							case 4://�������---���˹���---�༶��������
								incount_inqueue();
								admin_income_menu();
								break;
							case 5://��ʾ����δ�����û�
								user_arrearage();
								admin_income_menu();
								break;
							case 9://�����Ļ��ʷ��ѯ��Ϣ
								system("cls");
								printf("��ӭʹ��xxxxxxx��������ϵͳ");
								admin_income_menu();
								break;
							default:
								printf("\n������Ĵ������������¶�������˵�\n");
								admin_income_menu();
							}
						}
						break;
					case 2://�������---֧������
						admin_outcome_menu();
						while (1)
						{
							scanf("%d", &choose);
							getchar();//���ջس��ַ�
							if (choose == 0)//�������---֧������---�˻���һ��
							{
								admin_outcome_menu();
								admin_outcome_menu();
								break;
							}
							switch (choose)
							{
							case 1://�������---֧������---����֧��
								setup_log2();
								admin_outcome_menu();
								break;
							case 2://�������---֧������---��ʷ���ñ䶯��¼
								fprint_log();
								admin_outcome_menu();
								break;
							case 9://�����Ļ��ʷ��ѯ��Ϣ
								system("cls");
								printf("��ӭʹ��xxxxxxx��������ϵͳ");
								admin_outcome_menu();
								break;
							default:
								printf("\n������Ĵ������������¶�������˵�\n");
								admin_outcome_menu();
							}
						}
						break;
					case 3://�������---�����û�
						arrearage_situation();
						admin_bill_inform_menu();
						break;
					case 4://�������---����Ƿ�����
						user_arrearage();
						admin_bill_inform_menu();
						break;
					case 5://�����ʷ��¼
						fclear_log();
						admin_bill_inform_menu();
						break;
					case 6://��ʾ��ʷ���ñ䶯��¼
						fprint_log();
						admin_bill_inform_menu();
						break;
					case 7://��ѯĳѧ�����
						allaccount_administor();
						admin_bill_inform_menu();
						break;
					case 9://�����Ļ��ʷ��ѯ��Ϣ
						system("cls");
						printf("��ӭʹ��xxxxxxx��������ϵͳ");
						admin_bill_inform_menu();
						break;
					default:
						printf("\n������Ĵ������������¶�������˵�\n");
						admin_bill_inform_menu();
					}
				}
				break;
			case 9://�����Ļ��ʷ��ѯ��Ϣ
				system("cls");
				printf("��ӭʹ��xxxxxxx��������ϵͳ");
				admin_menu();
				break;
			default://�������
				printf("\n������Ĵ������������¶�������˵�\n");
				admin_menu();
			}
		}
	}
	else//�ο��˻���¼
	{
		user_menu();
		while (1)
		{
			scanf("%d", &choose);
			getchar();//���ջس��ַ�
			if (choose == 0)//��������
			{
				break;
			}
			if (choose == 1)
			{
				goto LOOP0;//�л��˻������µ�¼
			}
			switch (choose)
			{
			case 2://�����û�
				arrearage_situation();
				admin_income_menu();
				break;
			case 3://����Ƿ�����
				user_arrearage();
				admin_income_menu();
				break;
			case 4://��ʷ���ñ䶯��¼
				fprint_log();
				admin_income_menu();
				break;
			case 9://�����Ļ��ʷ��ѯ��Ϣ
				system("cls");
				printf("��ӭʹ��xxxxxxx��������ϵͳ");
				admin_income_menu();
				break;
			default:
				printf("\n������Ĵ������������¶�������˵�\n");
				admin_income_menu();
			}
		}
	}
	return 0;
}