#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 50
#define Min 0.0001

typedef struct BTNode
{
    char data;
    struct BTNode *lChild;
    struct BTNode *rChlid;
} BTNode;

int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 0;
    else
        return 1;
}
//操作数栈出栈两个元素进行运算的函数
void createBTNodeStackTopTwo(BTNode *BTNodeStack[], int *top1, char opStack[], int *top2)
{
    BTNode *BTNode1, *BTNode2, *result;
    char op;
    int flag;
    BTNode2 = BTNodeStack[(*top1)--];
    BTNode1 = BTNodeStack[(*top1)--];
    op = opStack[(*top2)--];
    result = (BTNode *)malloc(sizeof(BTNode));
    result->data = op;
    result->lChild = BTNode1;
    result->rChlid = BTNode2;
    BTNodeStack[++(*top1)] = result;
}

BTNode *createTree(char exp[])
{
    BTNode *BTNodeStack[maxSize];
    int top1 = -1;
    char opStack[maxSize];
    int top2 = -1;
    int i = 0;
    BTNode *p;
    while (exp[i] != '\0')
    {
        if ('0' <= exp[i] && exp[i] <= '9')
        {
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = exp[i];
            p->lChild = NULL;
            p->rChlid = NULL;
            BTNodeStack[++top1] = p;
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
                createBTNodeStackTopTwo(BTNodeStack, &top1, opStack, &top2);
            }
        }
        else if (exp[i] == ')')
        {
            while (opStack[top2] != '(')
            {
                createBTNodeStackTopTwo(BTNodeStack, &top1, opStack, &top2);
            }
            --top2;
            i++;
        }
    }
    while (top2 != -1)
    {
        createBTNodeStackTopTwo(BTNodeStack, &top1, opStack, &top2);
    }
    return BTNodeStack[top1];
}

void recrusion(BTNode *p)
{
    if (p != NULL)
    {
        recrusion(p->lChild);
        printf("%c", p->data);
        recrusion(p->rChlid);
    }
}

int main()
{
    string s = "3+4*5*(2+3)";
    char infix[11];
    strcpy(infix, s.c_str());
    BTNode *p = createTree(infix);
    recrusion(p);
    getchar();
    return 1;
}