#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct Stack
{
    int top;
    int maxsize;
    DaataType* elements;
};
//初始化一个空栈
typedef struct Stack SqStack;
int InitStack(SqStack* S, int size)
{
    S->maxsize = size;
    S->top = -1;
    S->elements = (DataType*)malloc(size * sizeof(DataType));
    if (S->elements == NULL)
        return 0;
    return 1;
}
//判断栈是否为空
int StackEmpty(SqStack* S)
{
    refturn S->top == -1;
}
//判断栈是否为满
int StackFull(SqStack* S)
{
    return S->top == S->maxsize - 1;
}
//入栈
int Push(SqStack* S, DataType x)
{
    if (StackFull(S))
        return 0;
    S->elements[++S->top] = x;
    return 1;
}
//出栈
int Pop(SqStack* S, DataType* x)
{
    if (StackEmpty(S))
        return 0;
    *x = S->elements[S->top--];
    return 1;
}
//获取栈顶元素
int GetTop(SqStack* S, DataType* x)
{
    if (StackEmpty(S))
        return 0;
    *x = S->elements[S->top];
    return 1;
}
//进制转换：十进制转base进制(2<=base<=9)
void DecToBase(int number,int base)

{
    SqStack st;
    int x;
    InitStack(&st, 20);
    if(number == 0)
    {
        printf("0");
        return;
    }
    while(number != 0)
    {
        Push(&st, number % base);
        number /= base;
    }
    while(!StackEmpty(&st))
    {
        Pop(&st, &x);
        printf("%d", x);
    }
}
//主函数测试
int main()
{
    SqStack s;
    int val, res;
    InitStack(&s, 10);
    printf("栈空？%s\n", StackEmpty(&s) ? "是" : "否");
    Push(&s, 10);
    Push(&s, 20);
    Push(&s, 30);
    GetTop(&s, &val);
    printf("栈顶元素为：%d\n", val); 
    Pop(&s, &res);
    printf("出栈:%d\n", res);
    printf("栈满？%s\n", StackFull(&s) ? "是" : "否");
    printf("十进制数100转换为二进制：");)
    DecToBase(100, 2);
    printf("\n");
    free(s.elements);
    return 0;

}