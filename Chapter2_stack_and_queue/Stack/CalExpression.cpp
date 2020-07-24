#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 50
#define Min 0.0001
//判断运算符优先级
int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 0;
    else
        return 1;
}
//运算函数
int calSub(float opnd1, char op, float opnd2, float *result)
{
    if (op == '+')
        *result = opnd1 + opnd2;
    if (op == '-')
        *result = opnd1 - opnd2;
    if (op == '*')
        *result = opnd1 * opnd2;
    if (op == '/')
    {
        if (abs(opnd2) < Min)
        {
            return 0;
        }
        else
        {
            (*result) = opnd1 / opnd2;
        }
    }

    return 1;
}
//操作数栈出栈两个元素进行运算的函数
int calStackTopTwo(float opndStack[], int *top1, char opStack[], int *top2)
{
    float opnd1, opnd2, result;
    char op;
    int flag;
    opnd2 = opndStack[(*top1)--];
    opnd1 = opndStack[(*top1)--];
    op = opStack[(*top2)--];
    flag = calSub(opnd1, op, opnd2, &result);
    if (flag == 0)
    {
        puts("ERROR");
    }
    opndStack[++(*top1)] = result;
    return flag;
}
//中缀式计算
float calInfix(char exp[])
{
    float opndStack[maxSize];
    int top1 = -1;
    char opStack[maxSize];
    int top2 = -1;
    int i = 0;
    while (exp[i] != '\0')
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            opndStack[++top1] = exp[i] - '0';
            i++;
        }
        else if (exp[i] == '(')
        {
            opStack[++top2] = '(';
            i++;
        }
        else if (exp[i] == '+' ||
                 exp[i] == '-' ||
                 exp[i] == '*' ||
                 exp[i] == '/')
        {
            if (top2 == -1 ||
                opStack[top2] == '(' ||
                getPriority(exp[i]) > getPriority(opStack[top2]))
            {
                opStack[++top2] = exp[i];
                i++;
            }
            else
            {
                int flag = calStackTopTwo(opndStack, &top1, opStack, &top2);
                if (flag == 0)
                {
                    return 0;
                }
            }
        }
        else if (exp[i] == ')')
        {
            while (opStack[top2] != '(')
            {
                int flag = calStackTopTwo(opndStack, &top1, opStack, &top2);
                if (flag == 0)
                {
                    return 0;
                }
            }
            --top2;
            i++;
        }
    }
    while (top2 != -1)
    {
        int flag = calStackTopTwo(opndStack, &top1, opStack, &top2);
        if (flag == 0)
        {
            return 0;
        }
    }
    return opndStack[top1];
}
//后缀表达式计算
float calPostFix(char exp[])
{
    float opndStack[maxSize];
    int top = -1;
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            opndStack[++top] = exp[i] - '0';
        }
        else
        {
            float opnd1, opnd2, result;
            char op;
            int flag;
            opnd2 = opndStack[top--];
            opnd1 = opndStack[top--];
            op = exp[i];
            flag = calSub(opnd1, op, opnd2, &result);
            if (flag == 0)
            {
                puts("ERROR");
                break;
            }
            opndStack[++top] = result;
        }
    }
    return opndStack[top];
}
//前缀表达式计算
float calPreFix(char exp[], int length)
{
    float opndStack[maxSize];
    int top = -1;
    int i;
    for (i = length - 1; i >= 0; i--)
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            opndStack[++top] = exp[i] - '0';
        }
        else
        {
            float opnd1, opnd2, result;
            char op;
            int flag;
            opnd1 = opndStack[top--];
            opnd2 = opndStack[top--];
            op = exp[i];
            flag = calSub(opnd1, op, opnd2, &result);
            if (flag == 0)
            {
                puts("ERROR");
                break;
            }
            opndStack[++top] = result;
        }
    }
    return opndStack[top];
}

int main()
{
    string s = "3+4*5*(2+3)";
    char infix[11];
    strcpy(infix, s.c_str());
    float result = calInfix(infix);
    printf("%f", result);
    printf("\n");

    string postFixString = "34523+**+";
    char postFix[11];
    strcpy(postFix, postFixString.c_str());
    float result2 = calPostFix(postFix);
    printf("%f", result2);
    printf("\n");
    
    string preFixString = "+3*4*5+23";
    char preFix[11];
    strcpy(preFix, preFixString.c_str());
    int length = sizeof(preFix) / sizeof(preFix[0]);
    float result3 = calPreFix(preFix, length);
    printf("%f", result3);

    getchar();
    return 0;
}