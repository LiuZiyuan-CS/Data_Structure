#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 50

int isMatched(char left, char right)
{
    if (left == '(' && right == ')')
        return 1;
    else if (left == '{' && right == '}')
        return 1;
    else if (left == '[' && right == ']')
        return 1;
    else
        return 0;
}

int isParentheseBalanced(char exp[])
{
    char parenStack[maxSize];
    int top = -1;
    int i;
    for (i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(' ||
            exp[i] == '{' ||
            exp[i] == '[')
        {
            parenStack[++top] = exp[i];
        }
        if (exp[i] == ')' ||
            exp[i] == '}' ||
            exp[i] == ']')
        {
            if (top == -1)
            {
                return 0;
            }
            char left = parenStack[top--];
            if (isMatched(left, exp[i]) == 0)
            {
                return 0;
            }
        }
    }
    if (top > -1)
    {
        return 0;
    }
    return 1;
}

int calF(int m)
{
    int cum = 1;
    int stack[maxSize];
    int top = -1;
    while (m != 0)
    {
        stack[++top] = m;
        m /= 3;
    }
    while (top != -1)
    {
        cum *= stack[top--];
    }
    return cum;
}
int main()
{
    string s = "{[()]}{()}";
    char parenthese[10];
    strcpy(parenthese, s.c_str());
    int result = isParentheseBalanced(parenthese);
    printf("%d", result);
    printf("\n");

    int m = 10;
    int r=calF(10);
    printf("%d", r);

    getchar();
    return 0;
}