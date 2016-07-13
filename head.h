/***********************************************************************/
/***********************深度优先搜索相关函数定义************************/
/***********************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h> 
#define maxsize 1000//栈长度
#define Maxsize 3//汉诺塔问题的阶数
//数据类型转换及顺序表构建
typedef struct{
	int data_s[Maxsize];
	int data_f[Maxsize];
}datatype;

//顺序栈定义
typedef struct{ 
	datatype data[maxsize+1];//栈数组
	int top; 				 //栈顶指针
}Seqstack;

//全局变量
datatype data_start;//初始状态节点
datatype data_end;//最终状态节点
datatype data;//临时数据存放器
datatype data_back[maxsize+1];//找到解后向上回溯至根节点
int length_hn;//汉诺塔的阶数
int seed=23;//随机数种子
int reserve[Maxsize];//用于还原原节点

Seqstack *Open_head;//open表
Seqstack *Closed_head;//closed表

/*********************函数声明*********************/
Seqstack *InitStack();//置空栈
void Stackempty(Seqstack *S);//判断栈是否为空
void Push(Seqstack *S,datatype x);//入栈
void Pop(Seqstack *S,datatype &x);//出栈
void Show(Seqstack *S);//输出栈内元素
/*********************函数声明*********************/
/***********************************************附属函数构建***********************************************/
//输出栈内元素
void Show_table(datatype value){
	printf("( ");
	for(int i=0;i<length_hn;i++){
		printf("%d ",value.data_s[i]);
	}
	printf(")\n");
}

//小菜单函数构建
bool select(){
	char select;
	char ch;//吸收干扰字符
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
/***********************************************附属函数构建***********************************************/

/***********************************************基本函数构建***********************************************/
//置空栈
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//判断栈是否为空
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("该栈为空！\n");
	}
	else{
		printf("该栈非空！\n");
	}
}

//入栈
void Push(Seqstack *S,datatype x){ 
	int i,j;//循环变量
	//插入数据前判断Open表中是否已有相等元素
	for(j=1;j<=S->top;j++){
		for(i=0;i<length_hn;i++){
			if(S->data[j].data_s[i]!=x.data_s[i]){
				break;
			}
		}
		if(i==length_hn){//Open表中已有相等元素
			break;
		}
	}
	if(j==S->top+1){//当前Open表中无相等元素
		for(j=1;j<=Closed_head->top;j++){
			for(i=0;i<length_hn;i++){
				if(Closed_head->data[j].data_s[i]!=x.data_s[i]){
					break;
				}
			}
			if(i==length_hn){//之前Open表中已有相等元素
				break;
			}
		}
		if(j==Closed_head->top+1){//之前Open表中无相等元素
			if (S->top==maxsize){
				printf("对不起，栈已满，您的数据插入失败！\n");
			}
			S->top++; 		
			for(i=0;i<length_hn;i++){
				S->data[S->top].data_f[i] = x.data_f[i];
				S->data[S->top].data_s[i] = x.data_s[i];
			}
		}	
	}	
}

//出栈
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("不好意思，Open表已空，该汉诺塔问题的DFS无解!\n");
		exit(0);
	}
	for(int i=0;i<length_hn;i++){
		x.data_f[i]=S->data[S->top].data_f[i];
		x.data_s[i]=S->data[S->top].data_s[i];
	}
	S->top--;
}

//检查输入是否正确
void Check_input(int value){
	if(value<1||value>3){
		printf("Warning:your input is wrong!(1 or 2 or 3)\n");
		exit(0);
	}
}

//汉诺塔问题的初值输入
void Init_Tnt(){
	int i;//循环变量
	int value;//问题初始化输入值容器
	printf("请输入您的汉诺塔的阶数(目前仅支持二阶和三阶):\n");
	scanf("%d",&length_hn);
	if(length_hn!=2&&length_hn!=3){
		printf("Warning: your input is wrong!(2 or 3)\n");
		exit(0);
	}
	
	printf("请输入您的初始状态节点(数字间用空格隔开):\n");
	for(i=0;i<length_hn;i++){
		scanf("%d",&value);
		Check_input(value);
		data_start.data_s[i]=value;
		data_start.data_f[i]=value;
	}

	printf("请输入您的终止状态节点(数字间用空格隔开):\n");
	for(i=0;i<length_hn;i++){
		scanf("%d",&value);
		Check_input(value);
		data_end.data_s[i]=value;
	}
	for(i=0;i<length_hn;i++){
		data_end.data_f[i]=0;
	}
}
/***********************************************基本函数构建***********************************************/

/***********************************************主要函数构建***********************************************/
//找到结果后向上回溯至根节点
void Get_way(datatype data){
	int n=1;//循环变量
	data_back[1]=data;
	for(int i=1;i<=Closed_head->top;i++){
		for(int j=0;j<length_hn;j++){
			if(data_back[n].data_f[j]!=Closed_head->data[i].data_s[j]){
				break;
			}
		}
		if(j==length_hn){
			n++;
			data_back[n]=Closed_head->data[i];
			for(int m=0;m<length_hn;m++){
				if(data_back[n].data_s[m]!=data_start.data_s[m]){
					break;
				}
			}
			if(m==length_hn){
				break;
			}
			else{
				i=0;
			}
		}
	}
	for(int m=n;n>=1;n--){
		printf("(");
		for(int l=0;l<length_hn;l++){
			printf(" %d",data_back[n].data_s[l]);
		}
		printf(" )\n");
	}
}
//汉诺塔问题的初始化描述
void Show_inithut(){
	int i;
	printf("初始状态: ( ");
	for(i=0;i<length_hn;i++){
		printf("%d ",data_start.data_s[i]);
	}
	printf(")\n");

	printf("终止状态: ( ");
	for(i=0;i<length_hn;i++){
		printf("%d ",data_end.data_s[i]);
	}
	printf(")\n");
}

//检测搜索是否成功
bool Test(){
	Pop(Open_head,data);
	Push(Closed_head,data);
	int i;//循环变量	
	for(i=0;i<length_hn;i++){
		if(data.data_s[i]!=data_end.data_s[i]){
			break;
		}
	}
	if(i==length_hn){
		Show_table(data);
		system("cls");		
		Show_inithut();
		printf("解的路径如下:\n");
		Get_way(data);
		printf("您的汉诺塔问题已成功求解!\n");
		return true;
	}
	else{
		Show_table(data);
		return false;
	}
}

//汉诺塔问题的具体求解
void Caculate_Hnt(){
	//Open表和closed表的初始化
	Open_head=InitStack();
	Closed_head=InitStack();
	Push(Open_head,data_start);

	printf("求解中间过程如下:\n");

start:
	//汉诺塔问题的具体操作
	while(!Test()){
		//for(i=0;i<length_hn;i++){}
	//小盘移动
		reserve[0]=data.data_s[0];
		reserve[1]=data.data_s[1];
		reserve[2]=data.data_s[2];
		for(int i=0;i<length_hn;i++){
			data.data_f[i]=data.data_s[i];
		}
		switch(data.data_s[0]){			
			case 1:		
				data.data_s[0]=2;
				Push(Open_head,data);
				data.data_s[0]=3;
				Push(Open_head,data);
				break;
				
			case 2:					
				data.data_s[0]=1;
				Push(Open_head,data);			
				data.data_s[0]=3;
				Push(Open_head,data);
				break;
				
			case 3:	
				data.data_s[0]=1;
				Push(Open_head,data);
				data.data_s[0]=2;	
				Push(Open_head,data);
				break;

			default:goto start;//避免移动休眠
		}		
	//中盘移动
		data.data_s[0]=reserve[0];
		switch(data.data_s[1]){
			data.data_s[0]=reserve[0];
			reserve[1]=data.data_s[1];
			case 1:	
				if(data.data_s[0]==1){
					goto start;//大盘上有小盘，大盘无法移动
				}			
				else if(data.data_s[0]==2){
					data.data_s[1]=3;
					Push(Open_head,data);
				}
				else{
					data.data_s[1]=2;
					Push(Open_head,data);
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2){
					goto start;//大盘上有小盘，大盘无法移动
				}				
				else if(data.data_s[0]==1){
					data.data_s[1]=3;
					Push(Open_head,data);
				}
				else{
					data.data_s[1]=1;
					Push(Open_head,data);
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==1){
					data.data_s[1]=2;
					Push(Open_head,data);
				}
				else{
					data.data_s[1]=1;
					Push(Open_head,data);
				}		
				break;

			default:goto start;//避免移动休眠
		}
		//大盘移动
		data.data_s[0]=reserve[0];
		data.data_s[1]=reserve[1];		
		switch(data.data_s[2]){			
			case 1:	
				if(data.data_s[0]==1||data.data_s[1]==1){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==2&&data.data_s[1]==2){
					data.data_s[1]=3;
					Push(Open_head,data);
				}
				else if(data.data_s[0]==3&&data.data_s[1]==3){
					data.data_s[1]=2;
					Push(Open_head,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2||data.data_s[1]==2){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==1&&data.data_s[1]==1){
					data.data_s[1]=3;
					Push(Open_head,data);
				}
				else if(data.data_s[0]==3&&data.data_s[1]==3){
					data.data_s[1]=1;
					Push(Open_head,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3||data.data_s[1]==3){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==2&&data.data_s[1]==2){
					data.data_s[1]=1;
					Push(Open_head,data);
				}
				else if(data.data_s[0]==1&&data.data_s[1]==1){
					data.data_s[1]=2;
					Push(Open_head,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;

			default:goto start;//避免移动休眠
		}
	}
}
/***********************************************主要函数构建***********************************************/


/***********************************************************************/
/***********************广度优先搜索相关函数定义************************/
/***********************************************************************/
//说明:一些全局的公用变量和附属函数在深度优先搜索中已经定义,此处不再赘述,读者进行相关阅读时,可参考深度优先搜索相关函数的定义

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h> 

//顺序队列定义
typedef struct{ 
	datatype data[maxsize+1];//栈数组
	int rear;//队尾指针
	int front;//队头指针
}Seqque;

Seqque *Open_head_Sque;//open表
Seqque *Closed_head_Sque;//closed表

/*********************函数声明*********************/
Seqque *InitSque();//置空栈
int Squeempty(Seqque *S);//判断栈是否为空
void Push_Sque(Seqque *S,datatype x);//入栈
void Pop_Sque(Seqque *S,datatype &x);//出栈
void Show_Sque(Seqque *S);//输出栈内元素
/*********************函数声明*********************/

/***********************************************基本函数构建***********************************************/
//置空队列
Seqque *InitSque(){
	Seqque *S;
    S=(Seqque *)malloc(sizeof(Seqque));
    S->front=S->rear=0;
    return(S); 
}

//判断队列是否为空
int Squeempty(Seqque *S){
    if(S->front==S->rear){
		return 0;
		printf("队列为空!\n");
	}
	else{
		return 1;
		printf("队列非空!\n");
	}
}

//入队
void Push_Sque(Seqque *S,datatype x){ 
	int i,j;//循环变量
	//插入数据前判断Open表中是否已有相等元素
	for(j=S->front+1;j<=S->rear;j++){
		for(i=0;i<length_hn;i++){
			if(S->data[j].data_s[i]!=x.data_s[i]){
				break;
			}
		}
		if(i==length_hn){//Open表中已有相等元素
			break;
		}
	}
	if(j==S->rear+1){//当前Open表中无相等元素
		for(j=Closed_head_Sque->front+1;j<=Closed_head_Sque->rear;j++){
			for(i=0;i<length_hn;i++){
				if(Closed_head_Sque->data[j].data_s[i]!=x.data_s[i]){
					break;
				}
			}
			if(i==length_hn){//之前Open表中已有相等元素
				break;
			}
		}
		if(j==Closed_head_Sque->rear+1){//之前Open表中无相等元素
			if (S->front==(S->rear+1)%maxsize){
				printf("对不起，该队列已满，您的数据插入失败！\n");
				exit(0);
			}
			S->rear=(S->rear+1)%maxsize;
			for(i=0;i<length_hn;i++){
				S->data[S->rear].data_f[i] = x.data_f[i];
				S->data[S->rear].data_s[i] = x.data_s[i];
			}
		}	
	}	
}

//出队
void Pop_Sque(Seqque *S,datatype &x){
	if(Squeempty(S)==0){
		printf("不好意思，Open表已空，您的汉诺塔BFS操作失败！\n");
		exit(0);
	}
	S->front=(S->front+1)%maxsize;
	for(int i=0;i<length_hn;i++){
		x.data_f[i]=S->data[S->front].data_f[i];
		x.data_s[i]=S->data[S->front].data_s[i];
	}
}

/***********************************************基本函数构建***********************************************/

/***********************************************主要函数构建***********************************************/
//找到结果后向上回溯至根节点
void Get_way_Sque(datatype data){
	int n=1;//循环变量
	data_back[1]=data;
	for(int i=Closed_head_Sque->front+1;i<=Closed_head_Sque->rear;i++){
		for(int j=0;j<length_hn;j++){
			if(data_back[n].data_f[j]!=Closed_head_Sque->data[i].data_s[j]){
				break;
			}
		}
		if(j==length_hn){
			n++;
			data_back[n]=Closed_head_Sque->data[i];
			for(int m=0;m<length_hn;m++){
				if(data_back[n].data_s[m]!=data_start.data_s[m]){
					break;
				}
			}
			if(m==length_hn){
				break;
			}
			else{
				i=0;
			}
		}
	}
	for(int m=n;n>=1;n--){
		printf("(");
		for(int l=0;l<length_hn;l++){
			printf(" %d",data_back[n].data_s[l]);
		}
		printf(" )\n");
	}
}

//检测搜索是否成功
bool Test_Sque(){
	Pop_Sque(Open_head_Sque,data);
	Push_Sque(Closed_head_Sque,data);
	int i;//循环变量	
	for(i=0;i<length_hn;i++){
		if(data.data_s[i]!=data_end.data_s[i]){
			break;
		}
	}
	if(i==length_hn){
		Show_table(data);
		system("cls");		
		Show_inithut();
		printf("解的路径如下:\n");
		Get_way_Sque(data);
		printf("您的汉诺塔问题已成功求解!\n");
		return true;
	}
	else{
		Show_table(data);
		return false;
	}
}

//汉诺塔问题的具体求解
void Caculate_Hnt_Sque(){
	//Open表和closed表的初始化
	Open_head_Sque=InitSque();
	Closed_head_Sque=InitSque();
	Push_Sque(Open_head_Sque,data_start);

	printf("求解中间过程如下:\n");

start:
	//汉诺塔问题的具体操作
	while(!Test_Sque()){
		//for(i=0;i<length_hn;i++){}
	//小盘移动
		reserve[0]=data.data_s[0];
		reserve[1]=data.data_s[1];
		reserve[2]=data.data_s[2];
		for(int i=0;i<length_hn;i++){
			data.data_f[i]=data.data_s[i];
		}
		switch(data.data_s[0]){			
			case 1:		
				data.data_s[0]=2;
				Push_Sque(Open_head_Sque,data);
				data.data_s[0]=3;
				Push_Sque(Open_head_Sque,data);
				break;
				
			case 2:					
				data.data_s[0]=1;
				Push_Sque(Open_head_Sque,data);			
				data.data_s[0]=3;
				Push_Sque(Open_head_Sque,data);
				break;
				
			case 3:	
				data.data_s[0]=1;
				Push_Sque(Open_head_Sque,data);
				data.data_s[0]=2;	
				Push_Sque(Open_head_Sque,data);
				break;

			default:goto start;//避免移动休眠
		}		
	//中盘移动
		data.data_s[0]=reserve[0];
		switch(data.data_s[1]){
			data.data_s[0]=reserve[0];
			reserve[1]=data.data_s[1];
			case 1:	
				if(data.data_s[0]==1){
					goto start;//大盘上有小盘，大盘无法移动
				}			
				else if(data.data_s[0]==2){
					data.data_s[1]=3;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					data.data_s[1]=2;
					Push_Sque(Open_head_Sque,data);
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2){
					goto start;//大盘上有小盘，大盘无法移动
				}				
				else if(data.data_s[0]==1){
					data.data_s[1]=3;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					data.data_s[1]=1;
					Push_Sque(Open_head_Sque,data);
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==1){
					data.data_s[1]=2;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					data.data_s[1]=1;
					Push_Sque(Open_head_Sque,data);
				}		
				break;

			default:goto start;//避免移动休眠
		}
		//大盘移动
		data.data_s[0]=reserve[0];
		data.data_s[1]=reserve[1];		
		switch(data.data_s[2]){			
			case 1:	
				if(data.data_s[0]==1||data.data_s[1]==1){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==2&&data.data_s[1]==2){
					data.data_s[1]=3;
					Push_Sque(Open_head_Sque,data);
				}
				else if(data.data_s[0]==3&&data.data_s[1]==3){
					data.data_s[1]=2;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2||data.data_s[1]==2){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==1&&data.data_s[1]==1){
					data.data_s[1]=3;
					Push_Sque(Open_head_Sque,data);
				}
				else if(data.data_s[0]==3&&data.data_s[1]==3){
					data.data_s[1]=1;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3||data.data_s[1]==3){
					goto start;//大盘上有小盘，大盘无法移动
				}
				else if(data.data_s[0]==2&&data.data_s[1]==2){
					data.data_s[1]=1;
					Push_Sque(Open_head_Sque,data);
				}
				else if(data.data_s[0]==1&&data.data_s[1]==1){
					data.data_s[1]=2;
					Push_Sque(Open_head_Sque,data);
				}
				else{
					goto start;//非大盘柱上有小盘，大盘无法移动
				}
				break;

			default:goto start;//避免移动休眠
		}
	}
}
/***********************************************主要函数构建***********************************************/