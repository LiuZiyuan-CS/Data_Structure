/**
 * 顺序表结构简单，所有就不采用结构体的方法定义。这种方法在考试中也是允许的
 * */

#include <stdio.h>
#include <stdlib.h>
#define maxSize 20

/*
 * 采用键盘输入插入数据,
 * 因为数组在c语言中属于引用型变量（其实c语言没有这种称呼，只是方便理解所以采用这种叫法），所以对数组本身进行操作是不需要传入指针的
 * 但是int型不属于引用型变量，所以必须加入指针才能对其引用
*/
void createSqList(int data[],int *length)
{
    int s;//    s用来记录从键盘上键入的数据
    scanf("%d", &(*length));
    for (int i = 0; i < (*length);i++)
    {
        scanf("%d", &s);
        data[i] = s;
    }
}

/**
 * 采用数组传入数据
 * */
void createSqList(int data[],int *length,int a[],int arrLength)
{
    (*length) = arrLength;
    for (int i = 0; i <arrLength;i++)
    {
        data[i] = a[i];
    }
}
//插入数据
int insertElem(int sqList[], int &length, int p, int e)
{
    if (p < 0 || p > length || length == maxSize)
    {
        return 0;
    }
    for (int i = length - 1; i >= p; i--)
    {
        sqList[i + 1] = sqList[i];
    }
    sqList[p] = e;
    length++;
    return 1;
}
//删除某个数据
int deleteElem(int sqList[], int &length, int p, int &e)
{
    if (p < 0 || p > length - 1)
    {
        return 0;
    }
    e = sqList[p];
    for (int i = p; i < length - 1; i++)
    {
        sqList[i] = sqList[i + 1];
    }
    length--;
    return 1;
}
/**
 * 顺序表逆置
 * */
int reverse(int data[], int *length,int left, int right)
{   if(right>(*length))
    {
        return 0;
    }
    int temp=0;
    for (int i = left, j = right; i < j; i++, j--)
    {
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    return 1;
}

int main()
{   
    //定义顺序表 一个长度为maxSize的数组，一个length的整型变量
    int data[maxSize] = {};
    int length;
    //
    /*使用键盘键入数据
    createSqList(data, &length);
    for (int i = 0; i < length;i++)
    {
        printf("%d", data[i]);
    }
    */
    
    /* 使用数组键入数据
    int a[5] = {3, 4, 9, 1, 5};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, arrLength);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }
    printf("\n");
    */

    /*插入元素，删除元素
    int a[5] = {3, 4, 9, 1, 5};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, arrLength);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }
    printf("\n");
    insertElem(data, length, 3, 99);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }

    int e;
    deleteElem(data, length, 3, e);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }
    printf("%d", e);
    */

    int a[5] = {3, 4, 9, 1, 5};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, arrLength);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }
    printf("\n");
    reverse(data,&arrLength, 1, 4);
    for (int i = 0; i < length;i++)
    {
        printf("%d \t", data[i]);
    }
    getchar();
    getchar();
    return 0;
}