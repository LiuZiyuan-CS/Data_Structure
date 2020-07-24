#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 50

int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 0;
    else
        return 1;
}
//中缀转后缀，中缀转后缀结果表达式不唯一
void infixToPostFix(char infix[], char s2[], int *top2) //s2是结果栈
{
    char s1[maxSize];
    int top1 = -1;
    int i = 0;
    while (infix[i] != '\0')
    {
        if ('0' <= infix[i] && infix[i] <= '9')
        {
            s2[++(*top2)] = infix[i];
            i++;
        }
        else if (infix[i] == '(')
        {
            s1[++top1] = '(';
            i++;
        }
        else if (infix[i] == '+' ||
                 infix[i] == '-' ||
                 infix[i] == '*' ||
                 infix[i] == '/')
        {
            if (top1 == -1 ||
                s1[top1] == '(' ||
                getPriority(infix[i]) > getPriority(s1[top1]))
            {
                s1[++top1] = infix[i];
                i++;
            }
            else
            {
                s2[++(*top2)] = s1[top1--];
            }
        }
        else if (infix[i] == ')')
        {
            while (s1[top1] != '(')
            {
                s2[++(*top2)] = s1[top1--];
            }
            top1--;
            i++;
        }
    }
    while (top1 != -1)
    {
        s2[++(*top2)] = s1[top1--];
    }
}

//中缀转前缀 结果表达式不唯一
void infixToPreFix(char infix[], int len, char s2[], int *top2)
{
    char s1[maxSize];
    int top1 = -1;
    int i = len - 1;
    while (i >= 0)
    {
        if ('0' <= infix[i] && infix[i] <= '9')
        {
            s2[++(*top2)] = infix[i];
            i--;
        }
        else if (infix[i] == ')')
        {
            s1[++top1] = ')';
            i--;
        }
        else if (infix[i] == '+' ||
                 infix[i] == '-' ||
                 infix[i] == '*' ||
                 infix[i] == '/')
        {
            if (top1 == -1 ||
                s1[top1] == ')' ||
                getPriority(infix[i]) >= getPriority(s1[top1]))
            {
                s1[++top1] = infix[i];
                i--;
            }
            else
            {
                s2[++(*top2)] = s1[top1--];
            }
        }
        else if (infix[i] == '(')
        {
            while (s1[top1] != ')')
            {
                s2[++(*top2)] = s1[top1--];
            }
            top1--;
            i--;
        }
    }
    while (top1 != -1)
    {
        s2[++(*top2)] = s1[top1--];
    }
}
int main()
{
    string s = "3+4*5*(2+3)";
    char infix[11];
    strcpy(infix, s.c_str());
     char s2[maxSize];
    int top2 = -1;
    infixToPostFix(infix, s2, &top2);
    for (int i = 0; i < 10; i++)
    {
        printf("%c", s2[i]);
    }
    printf("\n"); 

    top2 = -1;
    int length = sizeof(infix) / sizeof(infix[0]);
    infixToPreFix(infix,length,s2,&top2);
    for (int i = 10; i >= 0; i--)
    {
        printf("%c", s2[i]);
    }
    printf("\n");

    getchar();
    return 0;
}