#include <stdio.h>
#include <stdlib.h>
#define MAX 20
//��������ջ���ֱ����������������
struct SNode_Num 
{
    int datas[MAX];
    int top;
};
typedef struct SNode_Num OperateNum;
struct SNode_Symbol 
{
    char symbol[MAX];
    int top;
};
typedef struct SNode_Symbol OperateSymbol;
 
//ȡ����Ӧ����
int GetOperateNum(OperateNum *StackNum)
{
    return StackNum->datas[StackNum->top];
}
 
//ȡ����Ӧ�����
char GetOperateSymbol(OperateSymbol *StackSymbol)
{
    return StackSymbol->symbol[StackSymbol->top];
}
 
//��������ջ
void PushOperateNum(OperateNum *StackNum, int x)
{
    StackNum->top++;
    StackNum->datas[StackNum->top] = x;
}
 
//�������ջ
void PushOperateSymbol(OperateSymbol *StackSymbol, char ch)
{
    StackSymbol->top++;
    StackSymbol->symbol[StackSymbol->top] = ch;
}
 
//��������ջ
int PopOperateNum(OperateNum *StackNum)
{
    int num;
    num = StackNum->datas[StackNum->top];
    StackNum->top--;
    return num;
}
 
//�������ջ
char PopOperateSymbol(OperateSymbol *StackSymbol)
{
    char ch;
    ch = StackSymbol->symbol[StackSymbol->top];
    StackSymbol->top--;
    return ch;
}
 
//�ж�����ķ����Ƿ��������������
int IsOperateSymbolOrNum(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*'|| ch == '/' || ch == '\n') return 1;
    else return 0;
}
 
//�жϷ��ŵ����ȼ�
char Priority(char inputnum, char ch)
{
    switch(inputnum)
    {
        //�Ӽ���ͬһ�����ȼ���
        case '+':
        case '-':
        {
            if(ch == '+' || ch == '-') return '>';
            else if(ch == '*' || ch == '/') return '<';
            else return '>';
        }
            break;
 
        //�˳���ͬһ���ȼ�
        case '*':
        case '/':
        {
            if(ch == '+' || ch == '-') return '>';
            else if(ch == '*' || ch == '/') return '>';
            else return '>';
        }
            break;
 
        case '\n':
        {
            if(ch == '\n') return '=';
            else return '<';
        }
            break;
    }
}
int Calculate(int num1, char ch, int num2)
{
    int result;
    switch(ch)
    {
        case '+':
            result = num1 + num2;
            break;
        case '-':
			if(num1<num2)
			result=-1000;
			else
			result=num1-num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
			if(num1%num2==0)
            result = num1 / num2;
			else
				result=-1000;
    }
    return result;
}
//�����û�����ͼ�����
int MainCalc()
{
    //���������м���
    OperateNum datas;
    OperateSymbol symbol;
    int num1, num2, result, num;
    char ch, sign;
	//��ʼ��˳��ջ
	datas.top=-1;	//������ջ��ָ��
	symbol.top=-1;	//������ջ��ָ��
    //�ѻس�����Ĳ���������ջ��
    PushOperateSymbol(&symbol, '\n');
    ch = getchar();
    while((ch != '\n') || (GetOperateSymbol(&symbol) != '\n'))
    {
        if(!IsOperateSymbolOrNum(ch))
        {
            num = atoi(&ch);  //���ַ�ת��Ϊ����
            ch = getchar();   //��ȡ����
            while(!IsOperateSymbolOrNum(ch))
            {
                num = num * 10 + atoi(&ch);
                ch = getchar();   //��û������س�ʱ��������ȡ����
            }
            PushOperateNum(&datas, num);
        }
        else
        {
			//���ǵ�һ�����Ǹ��������
			if(ch=='-'&&symbol.top==0&&datas.top==-1)PushOperateNum(&datas, 0);
            switch(Priority(GetOperateSymbol(&symbol), ch))
            {
                //�ж����ȼ�����м���
                case '<':
                    PushOperateSymbol(&symbol, ch);
                    ch = getchar();
                    break;
                case '=':
                    sign = PopOperateSymbol(&symbol);
                    ch = getchar();  //��ȡ����
                    break;
                case '>':
                    sign = PopOperateSymbol(&symbol);
                    num2 = PopOperateNum(&datas);
                    num1 = PopOperateNum(&datas);
                    result = Calculate(num1, sign, num2);
                    PushOperateNum(&datas, result);
                    break;
 
            }
        }
    }
    result = GetOperateNum(&datas);
    return result;
}
 
int main(int argc, char *argv[])
{
    int result,cj=0,answer,i;
   
    for(i=0;i<10;){
    	getchar();
    	 printf("���%d���⣺",i+1);
    	result = MainCalc(); 
      	if(result>=0){
    		i++;
    	   printf("��������Ĵ𰸣�");
	       scanf("%d",&answer);
		   if(result==answer){
		   	cj+=10;
		   	printf("��ϲ�������\n");
		   } 
		   else{
		   	printf("Ŷ��������ˣ���ȷ���ǣ�%d\n",result);
		   } 
		}
		else{
			printf("�����Ϲ��������³���\n");
		}
		
	}
	printf("�������%d��\n",cj/10);
	printf("�����ܷ�Ϊ%d\n",cj);
}
    	


