#include <stdio.h>
#include <stdlib.h>
#define MAX 20
//定义两个栈，分别存放运算数和运算符
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
 
//取出相应的数
int GetOperateNum(OperateNum *StackNum)
{
    return StackNum->datas[StackNum->top];
}
 
//取出相应运算符
char GetOperateSymbol(OperateSymbol *StackSymbol)
{
    return StackSymbol->symbol[StackSymbol->top];
}
 
//运算数进栈
void PushOperateNum(OperateNum *StackNum, int x)
{
    StackNum->top++;
    StackNum->datas[StackNum->top] = x;
}
 
//运算符进栈
void PushOperateSymbol(OperateSymbol *StackSymbol, char ch)
{
    StackSymbol->top++;
    StackSymbol->symbol[StackSymbol->top] = ch;
}
 
//运算数退栈
int PopOperateNum(OperateNum *StackNum)
{
    int num;
    num = StackNum->datas[StackNum->top];
    StackNum->top--;
    return num;
}
 
//运算符退栈
char PopOperateSymbol(OperateSymbol *StackSymbol)
{
    char ch;
    ch = StackSymbol->symbol[StackSymbol->top];
    StackSymbol->top--;
    return ch;
}
 
//判断输入的符号是否是四则运算符号
int IsOperateSymbolOrNum(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*'|| ch == '/' || ch == '\n') return 1;
    else return 0;
}
 
//判断符号的优先级
char Priority(char inputnum, char ch)
{
    switch(inputnum)
    {
        //加减在同一个优先级上
        case '+':
        case '-':
        {
            if(ch == '+' || ch == '-') return '>';
            else if(ch == '*' || ch == '/') return '<';
            else return '>';
        }
            break;
 
        //乘除在同一优先级
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
//用于用户输入和计算结果
int MainCalc()
{
    //主函数进行计算
    OperateNum datas;
    OperateSymbol symbol;
    int num1, num2, result, num;
    char ch, sign;
	//初始化顺序栈
	datas.top=-1;	//操作数栈顶指针
	symbol.top=-1;	//操作符栈顶指针
    //把回车计算的操作符放在栈中
    PushOperateSymbol(&symbol, '\n');
    ch = getchar();
    while((ch != '\n') || (GetOperateSymbol(&symbol) != '\n'))
    {
        if(!IsOperateSymbolOrNum(ch))
        {
            num = atoi(&ch);  //将字符转换为整数
            ch = getchar();   //获取输入
            while(!IsOperateSymbolOrNum(ch))
            {
                num = num * 10 + atoi(&ch);
                ch = getchar();   //当没有输入回车时，继续获取输入
            }
            PushOperateNum(&datas, num);
        }
        else
        {
			//考虑第一个数是负数的情况
			if(ch=='-'&&symbol.top==0&&datas.top==-1)PushOperateNum(&datas, 0);
            switch(Priority(GetOperateSymbol(&symbol), ch))
            {
                //判断优先级后进行计算
                case '<':
                    PushOperateSymbol(&symbol, ch);
                    ch = getchar();
                    break;
                case '=':
                    sign = PopOperateSymbol(&symbol);
                    ch = getchar();  //获取输入
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
    	 printf("请第%d出题：",i+1);
    	result = MainCalc(); 
      	if(result>=0){
    		i++;
    	   printf("请输入你的答案：");
	       scanf("%d",&answer);
		   if(result==answer){
		   	cj+=10;
		   	printf("恭喜您答对了\n");
		   } 
		   else{
		   	printf("哦，您答错了，正确答案是：%d\n",result);
		   } 
		}
		else{
			printf("不符合规则，请重新出题\n");
		}
		
	}
	printf("您答对了%d题\n",cj/10);
	printf("您的总分为%d\n",cj);
}
    	


