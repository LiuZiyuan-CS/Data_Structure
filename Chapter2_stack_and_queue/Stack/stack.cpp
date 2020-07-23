#include <stdio.h>
#include <stdlib.h>

#define maxSize 50
int isEmpty(int stack[], int top)
{
    if (top == -1)
        return 1; //1表示空了
    else
        return 0; //0代表没空
}
int isFull(int stack[], int top)
{
    if (top == maxSize - 1)
        return 1; //1表示栈满
    else
        return 0; //0表示栈未满
}
int push(int stack[], int *top, int elem)
{
    if (isFull(stack, *top) == 1)
        return 0; //栈满，push失败
    else
    {
        stack[++(*top)] = elem;
        return elem;
    }
}
int pop(int stack[], int *top)
{
    if (isEmpty(stack, *top) == 1)
        return 0; //栈空，pop失败
    else
    {
        return stack[(*top)--];
    }
}

int main()
{
    //建立一个栈
    int stack[maxSize] = {1, 2, 3, 4};
    int top = 3;

    int result = isEmpty(stack, top);
    printf("%d", result);
    printf("\n", result);

    push(stack, &top, 5);
    for (int i = 0; i <= top; i++)
    {
        printf("%d", stack[i]);
    }
    printf("\n", result);
    
    pop(stack, &top);
    for (int i = 0; i <= top; i++)
    {
        printf("%d", stack[i]);
    }
    getchar();
    return 0;
}