/*===================================================
任务：利用深度优先搜索解决汉诺塔问题
作者：李伟康_1240069_12级计算机二班
时间：2014年5月8日
版本：v1.0
===================================================*/
#include "head.h"

int main()
{
	//用户菜单界面
	int choice=0;
	do{
		printf("*******************汉诺塔问题的求解*******************\n");
		printf("*1.深度优先搜索                                      *\n");
		printf("*2.广度优先搜索                                      *\n");
		printf("*3.退出                                              *\n");
		printf("******************************************************\n");	
		printf("请输入您的选择:");
		scanf("%d",&choice);
		switch(choice){
			case 1:	system("cls");
					//汉诺塔问题的初值输入
					Init_Tnt();
					Sleep(1000);
					system("cls");
					//汉诺塔问题的初始化描述
					Show_inithut();
					//汉诺塔问题的具体求解
					Caculate_Hnt();
					if(select()){
						system("cls");	
						main();
					}
					else return 0;
					break;

			case 2:	system("cls");
					//汉诺塔问题的初值输入
					Init_Tnt();
					Sleep(1000);
					system("cls");
					//汉诺塔问题的初始化描述
					Show_inithut();
					//汉诺塔问题的具体求解
					Caculate_Hnt_Sque();
					if(select()){
						system("cls");	
						main();
					}
					else return 0;
					break;

			case 3:	exit(0);
					break;

			default:printf("不好意思，您的输入有误(1-3)！\n");
		}
	}while(choice=3);	
	return 0;
}
