#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 15
#define Min 0.0001

typedef struct BTNode
{
    char data;
    struct BTNode *lChild;
    struct BTNode *rChlid;
} BTNode;
void visit(BTNode *p)
{
    printf("%c", p->data);
}
//先序遍历递归调用
void Prerecursion(BTNode *root)
{
    if (root != NULL)
    {
        visit(root);
        Prerecursion(root->lChild);
        Prerecursion(root->rChlid);
    }
}
//中序遍历递归调用
void Inrecrusion(BTNode *root)
{
    if (root != NULL)
    {
        Inrecrusion(root->lChild);
        visit(root);
        Inrecrusion(root->rChlid);
    }
}
//后序遍历递归调用
void Postrecursion(BTNode *root)
{
    if (root != NULL)
    {
        Postrecursion(root->lChild);
        Postrecursion(root->rChlid);
        visit(root);
    }
}

//先序遍历非递归
void preorderNonrecursion(BTNode *root)
{
    if (root != NULL)
    {
        BTNode *Stack[maxSize];
        int top = -1;
        BTNode *p = NULL;
        Stack[++top] = root;
        while (top != -1)
        {
            p = Stack[top--];
            visit(p);
            if (p->rChlid != NULL)
            {
                Stack[++top] = p->rChlid;
            }
            if (p->lChild != NULL)
            {
                Stack[++top] = p->lChild;
            }
        }
    }
}

//中序遍历非递归
void inorderNonrecursion(BTNode *root)
{
    if (root != NULL)
    {
        BTNode *Stack[maxSize];
        int top = -1;
        BTNode *p = NULL;
        p = root;
        while (top != -1 || p != NULL)
        {
            while (p != NULL)
            {
                Stack[++top] = p;
                p = p->lChild;
            }
            if (top != -1)
            {
                p = Stack[top--];
                visit(p);
                p = p->rChlid;
            }
        }
    }
}

//后序遍历非递归
void postorderNonrecursion(BTNode *root)
{
    if (root != NULL)
    {
        BTNode *Stack1[maxSize];
        int top1 = -1;
        BTNode *Stack2[maxSize];
        int top2 = -1;
        BTNode *p = NULL;
        Stack1[++top1] = root;
        while (top1 != -1)
        {
            p = Stack1[top1--];
            Stack2[++top2] = p;
            if (p->lChild != NULL)
            {
                Stack1[++top1] = p->lChild;
            }
            if (p->rChlid != NULL)
            {
                Stack1[++top1] = p->rChlid;
            }
        }
        while (top2 != -1)
        {
            p = Stack2[top2--];
            visit(p);
        }
    }
}

//二叉树层次遍历
void level(BTNode *root)
{
    int front, rear;
    BTNode *que[maxSize];
    front = rear = 0;
    BTNode *p = NULL;
    p = root;
    rear = (rear + 1) % maxSize;
    que[rear] = p;
    while (front != rear)
    {
        front = (front + 1) % maxSize;
        p = que[front];
        visit(p);
        if (p->lChild != NULL)
        {
            rear = (rear + 1) % maxSize;
            que[rear] = p->lChild;
        }

        if (p->rChlid != NULL)
        {
            rear = (rear + 1) % maxSize;
            que[rear] = p->rChlid;
        }
    }
}

int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 0;
    else
        return 1;
}
//二叉树栈出栈两个元素进行建立二叉树节点的函数
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
        if (fabs(opnd2) < Min)
            return 0;
        else
            *result = opnd1 / opnd2;
    }
    return 1;
}

float cal(BTNode *root)
{
    if (root->lChild == NULL && root->rChlid == NULL)
    {
        return root->data - '0';
    }
    else
    {
        float opnd1 = cal(root->lChild);
        float opnd2 = cal(root->rChlid);

        float result;
        calSub(opnd1, root->data, opnd2, &result);
        return result;
    }
}

int main()
{
    string s = "3+4*5*(2+3)";
    char infix[11];
    strcpy(infix, s.c_str());
    BTNode *p = createTree(infix);
    Prerecursion(p);
    printf("\n");
    printf("\n");
    Inrecrusion(p);
    printf("\n");
    printf("\n");
    Postrecursion(p);
    printf("\n");
    printf("\n");
    preorderNonrecursion(p);
    printf("\n");
    printf("\n");
    inorderNonrecursion(p);
    printf("\n");
    printf("\n");
    postorderNonrecursion(p);
    printf("\n");
    printf("\n");
    level(p);
    printf("\n");
    printf("\n");
    float result = cal(p);
    printf("%f", result);
    getchar();
    return 1;
}