#include <stdio.h>
#include <stdlib.h>
#define maxSize 10
float findmax(float A[], int i, int j)
{
    float max;
    if (i == j)
        return A[i];
    else
    {
        max = findmax(A, i + 1, j);
        if (A[i] > max)
            return A[i];
        else
            return max;
    }
}
float sum(float A[], int i, int j)
{
    if (i == j)
        return A[i];
    else
        return A[i] + sum(A, i + 1, j);
}

float avg(float A[], int i, int j)
{
    float s;
    if (i == j)
        return A[i];
    else
    {
        s = (A[i] + (j - i) * avg(A, i + 1, j)) / (j - i + 1);
        return s;
    }
}

void move(int A[], int len)
{
    int i = -1, j;
    int temp;
    for (j = 0; j < len; j++)
    {
        if (A[j] % 2 != 0)
        {
            i++;
            if (i != j)
            {
                temp = A[j];
                A[j] = A[i];
                A[i] = temp;
            }
        }
    }
}

void printMin(int A[][maxSize], int m, int n)
{
    int i, j, k, min, minj;
    int flag;
    for (i = 0; i < m; i++)
    {
        min = A[i][0];
        minj = 0;
        for (j = 0; j < n; j++)
        {
            if (min > A[i][j])
            {
                min = A[i][j];
                minj = j;
            }
        }
        flag = 1;
        for (k = 0; k < m;k++)
        {
            if(min>A[k][minj])
            {
                flag = 0;
                break;
            }
        }
        if(flag)
        {
            printf("%d,[ %d , %d ]",min,i, minj);
        }
        printf("\n");
    }
}

int main()
{
    int a[8] = {3, 6, 7, 7, 5, 4, 9, 8};
    int A[][maxSize] = {{3, 8, 1}, {7, 2, 9}, {1, 6, 8}};
    for (int i = 0; i < 3;i++)
    {
        for (int j = 0; j < 3;j++)
        {
            printf("%d", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printMin(A, 3, 3);
    getchar();
    return 0;
}
