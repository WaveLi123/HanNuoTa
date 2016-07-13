/***********************************************************************/
/***********************�������������غ�������************************/
/***********************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h> 
#define maxsize 1000//ջ����
#define Maxsize 3//��ŵ������Ľ���
//��������ת����˳�����
typedef struct{
	int data_s[Maxsize];
	int data_f[Maxsize];
}datatype;

//˳��ջ����
typedef struct{ 
	datatype data[maxsize+1];//ջ����
	int top; 				 //ջ��ָ��
}Seqstack;

//ȫ�ֱ���
datatype data_start;//��ʼ״̬�ڵ�
datatype data_end;//����״̬�ڵ�
datatype data;//��ʱ���ݴ����
datatype data_back[maxsize+1];//�ҵ�������ϻ��������ڵ�
int length_hn;//��ŵ���Ľ���
int seed=23;//���������
int reserve[Maxsize];//���ڻ�ԭԭ�ڵ�

Seqstack *Open_head;//open��
Seqstack *Closed_head;//closed��

/*********************��������*********************/
Seqstack *InitStack();//�ÿ�ջ
void Stackempty(Seqstack *S);//�ж�ջ�Ƿ�Ϊ��
void Push(Seqstack *S,datatype x);//��ջ
void Pop(Seqstack *S,datatype &x);//��ջ
void Show(Seqstack *S);//���ջ��Ԫ��
/*********************��������*********************/
/***********************************************������������***********************************************/
//���ջ��Ԫ��
void Show_table(datatype value){
	printf("( ");
	for(int i=0;i<length_hn;i++){
		printf("%d ",value.data_s[i]);
	}
	printf(")\n");
}

//С�˵���������
bool select(){
	char select;
	char ch;//���ո����ַ�
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
/***********************************************������������***********************************************/

/***********************************************������������***********************************************/
//�ÿ�ջ
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//�ж�ջ�Ƿ�Ϊ��
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("��ջΪ�գ�\n");
	}
	else{
		printf("��ջ�ǿգ�\n");
	}
}

//��ջ
void Push(Seqstack *S,datatype x){ 
	int i,j;//ѭ������
	//��������ǰ�ж�Open�����Ƿ��������Ԫ��
	for(j=1;j<=S->top;j++){
		for(i=0;i<length_hn;i++){
			if(S->data[j].data_s[i]!=x.data_s[i]){
				break;
			}
		}
		if(i==length_hn){//Open�����������Ԫ��
			break;
		}
	}
	if(j==S->top+1){//��ǰOpen���������Ԫ��
		for(j=1;j<=Closed_head->top;j++){
			for(i=0;i<length_hn;i++){
				if(Closed_head->data[j].data_s[i]!=x.data_s[i]){
					break;
				}
			}
			if(i==length_hn){//֮ǰOpen�����������Ԫ��
				break;
			}
		}
		if(j==Closed_head->top+1){//֮ǰOpen���������Ԫ��
			if (S->top==maxsize){
				printf("�Բ���ջ�������������ݲ���ʧ�ܣ�\n");
			}
			S->top++; 		
			for(i=0;i<length_hn;i++){
				S->data[S->top].data_f[i] = x.data_f[i];
				S->data[S->top].data_s[i] = x.data_s[i];
			}
		}	
	}	
}

//��ջ
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("������˼��Open���ѿգ��ú�ŵ�������DFS�޽�!\n");
		exit(0);
	}
	for(int i=0;i<length_hn;i++){
		x.data_f[i]=S->data[S->top].data_f[i];
		x.data_s[i]=S->data[S->top].data_s[i];
	}
	S->top--;
}

//��������Ƿ���ȷ
void Check_input(int value){
	if(value<1||value>3){
		printf("Warning:your input is wrong!(1 or 2 or 3)\n");
		exit(0);
	}
}

//��ŵ������ĳ�ֵ����
void Init_Tnt(){
	int i;//ѭ������
	int value;//�����ʼ������ֵ����
	printf("���������ĺ�ŵ���Ľ���(Ŀǰ��֧�ֶ��׺�����):\n");
	scanf("%d",&length_hn);
	if(length_hn!=2&&length_hn!=3){
		printf("Warning: your input is wrong!(2 or 3)\n");
		exit(0);
	}
	
	printf("���������ĳ�ʼ״̬�ڵ�(���ּ��ÿո����):\n");
	for(i=0;i<length_hn;i++){
		scanf("%d",&value);
		Check_input(value);
		data_start.data_s[i]=value;
		data_start.data_f[i]=value;
	}

	printf("������������ֹ״̬�ڵ�(���ּ��ÿո����):\n");
	for(i=0;i<length_hn;i++){
		scanf("%d",&value);
		Check_input(value);
		data_end.data_s[i]=value;
	}
	for(i=0;i<length_hn;i++){
		data_end.data_f[i]=0;
	}
}
/***********************************************������������***********************************************/

/***********************************************��Ҫ��������***********************************************/
//�ҵ���������ϻ��������ڵ�
void Get_way(datatype data){
	int n=1;//ѭ������
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
//��ŵ������ĳ�ʼ������
void Show_inithut(){
	int i;
	printf("��ʼ״̬: ( ");
	for(i=0;i<length_hn;i++){
		printf("%d ",data_start.data_s[i]);
	}
	printf(")\n");

	printf("��ֹ״̬: ( ");
	for(i=0;i<length_hn;i++){
		printf("%d ",data_end.data_s[i]);
	}
	printf(")\n");
}

//��������Ƿ�ɹ�
bool Test(){
	Pop(Open_head,data);
	Push(Closed_head,data);
	int i;//ѭ������	
	for(i=0;i<length_hn;i++){
		if(data.data_s[i]!=data_end.data_s[i]){
			break;
		}
	}
	if(i==length_hn){
		Show_table(data);
		system("cls");		
		Show_inithut();
		printf("���·������:\n");
		Get_way(data);
		printf("���ĺ�ŵ�������ѳɹ����!\n");
		return true;
	}
	else{
		Show_table(data);
		return false;
	}
}

//��ŵ������ľ������
void Caculate_Hnt(){
	//Open���closed��ĳ�ʼ��
	Open_head=InitStack();
	Closed_head=InitStack();
	Push(Open_head,data_start);

	printf("����м��������:\n");

start:
	//��ŵ������ľ������
	while(!Test()){
		//for(i=0;i<length_hn;i++){}
	//С���ƶ�
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

			default:goto start;//�����ƶ�����
		}		
	//�����ƶ�
		data.data_s[0]=reserve[0];
		switch(data.data_s[1]){
			data.data_s[0]=reserve[0];
			reserve[1]=data.data_s[1];
			case 1:	
				if(data.data_s[0]==1){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//��������С�̣������޷��ƶ�
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

			default:goto start;//�����ƶ�����
		}
		//�����ƶ�
		data.data_s[0]=reserve[0];
		data.data_s[1]=reserve[1];		
		switch(data.data_s[2]){			
			case 1:	
				if(data.data_s[0]==1||data.data_s[1]==1){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2||data.data_s[1]==2){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3||data.data_s[1]==3){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;

			default:goto start;//�����ƶ�����
		}
	}
}
/***********************************************��Ҫ��������***********************************************/


/***********************************************************************/
/***********************�������������غ�������************************/
/***********************************************************************/
//˵��:һЩȫ�ֵĹ��ñ����͸�����������������������Ѿ�����,�˴�����׸��,���߽�������Ķ�ʱ,�ɲο��������������غ����Ķ���

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h> 

//˳����ж���
typedef struct{ 
	datatype data[maxsize+1];//ջ����
	int rear;//��βָ��
	int front;//��ͷָ��
}Seqque;

Seqque *Open_head_Sque;//open��
Seqque *Closed_head_Sque;//closed��

/*********************��������*********************/
Seqque *InitSque();//�ÿ�ջ
int Squeempty(Seqque *S);//�ж�ջ�Ƿ�Ϊ��
void Push_Sque(Seqque *S,datatype x);//��ջ
void Pop_Sque(Seqque *S,datatype &x);//��ջ
void Show_Sque(Seqque *S);//���ջ��Ԫ��
/*********************��������*********************/

/***********************************************������������***********************************************/
//�ÿն���
Seqque *InitSque(){
	Seqque *S;
    S=(Seqque *)malloc(sizeof(Seqque));
    S->front=S->rear=0;
    return(S); 
}

//�ж϶����Ƿ�Ϊ��
int Squeempty(Seqque *S){
    if(S->front==S->rear){
		return 0;
		printf("����Ϊ��!\n");
	}
	else{
		return 1;
		printf("���зǿ�!\n");
	}
}

//���
void Push_Sque(Seqque *S,datatype x){ 
	int i,j;//ѭ������
	//��������ǰ�ж�Open�����Ƿ��������Ԫ��
	for(j=S->front+1;j<=S->rear;j++){
		for(i=0;i<length_hn;i++){
			if(S->data[j].data_s[i]!=x.data_s[i]){
				break;
			}
		}
		if(i==length_hn){//Open�����������Ԫ��
			break;
		}
	}
	if(j==S->rear+1){//��ǰOpen���������Ԫ��
		for(j=Closed_head_Sque->front+1;j<=Closed_head_Sque->rear;j++){
			for(i=0;i<length_hn;i++){
				if(Closed_head_Sque->data[j].data_s[i]!=x.data_s[i]){
					break;
				}
			}
			if(i==length_hn){//֮ǰOpen�����������Ԫ��
				break;
			}
		}
		if(j==Closed_head_Sque->rear+1){//֮ǰOpen���������Ԫ��
			if (S->front==(S->rear+1)%maxsize){
				printf("�Բ��𣬸ö����������������ݲ���ʧ�ܣ�\n");
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

//����
void Pop_Sque(Seqque *S,datatype &x){
	if(Squeempty(S)==0){
		printf("������˼��Open���ѿգ����ĺ�ŵ��BFS����ʧ�ܣ�\n");
		exit(0);
	}
	S->front=(S->front+1)%maxsize;
	for(int i=0;i<length_hn;i++){
		x.data_f[i]=S->data[S->front].data_f[i];
		x.data_s[i]=S->data[S->front].data_s[i];
	}
}

/***********************************************������������***********************************************/

/***********************************************��Ҫ��������***********************************************/
//�ҵ���������ϻ��������ڵ�
void Get_way_Sque(datatype data){
	int n=1;//ѭ������
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

//��������Ƿ�ɹ�
bool Test_Sque(){
	Pop_Sque(Open_head_Sque,data);
	Push_Sque(Closed_head_Sque,data);
	int i;//ѭ������	
	for(i=0;i<length_hn;i++){
		if(data.data_s[i]!=data_end.data_s[i]){
			break;
		}
	}
	if(i==length_hn){
		Show_table(data);
		system("cls");		
		Show_inithut();
		printf("���·������:\n");
		Get_way_Sque(data);
		printf("���ĺ�ŵ�������ѳɹ����!\n");
		return true;
	}
	else{
		Show_table(data);
		return false;
	}
}

//��ŵ������ľ������
void Caculate_Hnt_Sque(){
	//Open���closed��ĳ�ʼ��
	Open_head_Sque=InitSque();
	Closed_head_Sque=InitSque();
	Push_Sque(Open_head_Sque,data_start);

	printf("����м��������:\n");

start:
	//��ŵ������ľ������
	while(!Test_Sque()){
		//for(i=0;i<length_hn;i++){}
	//С���ƶ�
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

			default:goto start;//�����ƶ�����
		}		
	//�����ƶ�
		data.data_s[0]=reserve[0];
		switch(data.data_s[1]){
			data.data_s[0]=reserve[0];
			reserve[1]=data.data_s[1];
			case 1:	
				if(data.data_s[0]==1){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//��������С�̣������޷��ƶ�
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

			default:goto start;//�����ƶ�����
		}
		//�����ƶ�
		data.data_s[0]=reserve[0];
		data.data_s[1]=reserve[1];		
		switch(data.data_s[2]){			
			case 1:	
				if(data.data_s[0]==1||data.data_s[1]==1){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;
								
			case 2:	
				if(data.data_s[0]==2||data.data_s[1]==2){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;
					
			case 3:	
				if(data.data_s[0]==3||data.data_s[1]==3){
					goto start;//��������С�̣������޷��ƶ�
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
					goto start;//�Ǵ���������С�̣������޷��ƶ�
				}
				break;

			default:goto start;//�����ƶ�����
		}
	}
}
/***********************************************��Ҫ��������***********************************************/