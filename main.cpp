/*===================================================
������������������������ŵ������
���ߣ���ΰ��_1240069_12�����������
ʱ�䣺2014��5��8��
�汾��v1.0
===================================================*/
#include "head.h"

int main()
{
	//�û��˵�����
	int choice=0;
	do{
		printf("*******************��ŵ����������*******************\n");
		printf("*1.�����������                                      *\n");
		printf("*2.�����������                                      *\n");
		printf("*3.�˳�                                              *\n");
		printf("******************************************************\n");	
		printf("����������ѡ��:");
		scanf("%d",&choice);
		switch(choice){
			case 1:	system("cls");
					//��ŵ������ĳ�ֵ����
					Init_Tnt();
					Sleep(1000);
					system("cls");
					//��ŵ������ĳ�ʼ������
					Show_inithut();
					//��ŵ������ľ������
					Caculate_Hnt();
					if(select()){
						system("cls");	
						main();
					}
					else return 0;
					break;

			case 2:	system("cls");
					//��ŵ������ĳ�ֵ����
					Init_Tnt();
					Sleep(1000);
					system("cls");
					//��ŵ������ĳ�ʼ������
					Show_inithut();
					//��ŵ������ľ������
					Caculate_Hnt_Sque();
					if(select()){
						system("cls");	
						main();
					}
					else return 0;
					break;

			case 3:	exit(0);
					break;

			default:printf("������˼��������������(1-3)��\n");
		}
	}while(choice=3);	
	return 0;
}
