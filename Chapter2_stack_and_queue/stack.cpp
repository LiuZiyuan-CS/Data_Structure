#include <stdio.h>
#include <stdlib.h>

#define maxSize 50
int isEmpty(int stack[],int top)
{
    if(top==-1)
    {
        return 0;//0表示空了
    }
    else
    {
        return 1;//1代表没空
    }
}
void push(int stack[],int *top)
{
    
}


int main()
{
    //建立一个栈
    int stack[maxSize];
    int top = -1;
    int result=isEmpty(stack, top);
    printf("%d", result);
    getchar();
    return 0;
}