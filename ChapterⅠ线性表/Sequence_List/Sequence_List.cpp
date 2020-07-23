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
void createSqList(int data[], int *length)
{
    int s; //    s用来记录从键盘上键入的数据
    scanf("%d", &(*length));
    for (int i = 0; i < (*length); i++)
    {
        scanf("%d", &s);
        data[i] = s;
    }
}

/**
 * 采用数组传入数据
 * */
void createSqList(int data[], int *length, int a[], int arrLength)
{
    (*length) = arrLength;
    for (int i = 0; i < arrLength; i++)
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
int reverse(int data[], int *length, int left, int right)
{
    if (right > (*length))
    {
        return 0;
    }
    int temp = 0;
    for (int i = left, j = right; i < j; i++, j--)
    {
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    return 1;
}
/**
 * 顺序表取最大值
 * */
int getMaxElem(int data[], int *length, int *maxIdx)
{
    int max = data[0];
    (*maxIdx) = 0;
    for (int i = 0; i < (*length); i++)
    {
        if (max < data[i])
        {
            max = data[i];
            (*maxIdx) = i;
        }
    }
    return max;
}
/**
 * 顺序表取最小值
 * */
int getMinElem(int data[], int *length, int *minIdx)
{
    int min = data[0];
    (*minIdx) = 0;
    for (int i = 0; i < (*length); i++)
    {
        if (min > data[i])
        {
            min = data[i];
            (*minIdx) = i;
        }
    }
    return min;
}

/**
 * 顺序表归并：已知两个已排序好的顺序表，对其归并，
 * 因为考试中一般不判断c会不会溢出的问题，所以我们考虑理想状态——数组C无限大
 * 基本原理：依次取出a,b数组中最小的元素进行比较，较小的将其放入c数组中，若该元素来自a，则a的下标后移，若该元素来自b，则b的下标后移
 * */
void mergeArray(int a[], int aLength, int b[], int bLength, int c[])
{
    int i = 0, j = 0;                  //i,j分别表示循环时的a，b数组下标
    int k = 0;                         //k表示c的数组下标
    while (i < aLength && j < bLength) //两个数组都未循环结束时。
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i++]; //因为k++,i++ 是进行先赋值，在＋1，若不理解可以写成c[k]=a[i];k++;i++
        }
        else
        {
            c[k++] = b[j++];
        }
    }
    //此时两个数组中长度较小那个数组已经循环结束，我们只需将另一个数组的中的剩余元素依次加入即可
    while (i < aLength)
    {
        c[k++] = a[i++];
    }
    while (j < bLength)
    {
        c[k++] = b[j++];
    }
}

/** 万能解法
 * ⭐划分问题(个人认为比较难理解）⭐：
 * 基本原理:
 * 枢轴（枢轴不一定是比较元素，只是枢轴常用作比较元素来进行划分），枢轴是顺序表中的任意一个元素。
 * 比较元素：比较元素comp可以任取，
 *          若comp大于枢轴的值，则顺序表的划分分界线在函数结束后枢轴所在位置的右侧
 *          若comp小于枢轴的值，则顺序表的划分分界线在函数结束后枢轴所在位置的左侧
 *          若comp等于枢轴的值，则顺序表的划分分界线在函数结束后枢轴所在位置，       
 * 1、将枢轴放到顺序表的第一个，将枢轴的值赋给temp，
 * 2、定义两个变量 i,j分别指向顺序表的首位和末端，使用while循环，循环条件为：i<j时
 * （❗❗❗3-6是平行的步骤，有先后顺序的执行，但是不是互相嵌套的）
 *      3、使用while循环，循环条件为 i<j且 arr[j]大于等于枢轴comp，则 j--，直到找到arr[j]<comp时，结束循环
 *      4、此时判断i<j（因为对于第三步来说结束循环的条件有两个：Ⅰ.i>=j,Ⅱ.arr[j]<comp),
 *         如果i<j为真，则arr[i]=arr[j](不用担心arr[i]的值被覆盖，因为此时i=0，即枢轴的值保存在了comp中)
 *      5、使用while循环, 循环条件为 i<j且 arr[i]小于等于枢轴comp，则 i++, 直到找到arr[i]>comp时，结束循环
 *      6、此时判断i<j(因为对于第5步来说结束循环的条件有两个：Ⅰ.i>=j,Ⅱ.arr[i]>comp)
 *         如果i<j为真，则arr[j]=arr[i](不用担心arr[j]的值被覆盖，因为此时j在上一个while循环跳出以后未发生改变，而且arr[j]的值已经移到了原来枢轴在的位置)
 * 7、假定此时最外的大while循环还未结束则继续执行3-6，
 *    此时arr[i]=arr[j](不用担心arr[i]的值被覆盖,因为i在上一次关于i的小循环跳出后未发生改变，而arr[i]的值已经移到了之前第6步结束时arr[j]的位置)
 * 8、继续执行下一个小的while循环
 *    此时arr[j]=arr[i](不用担心arr[j]的值被覆盖,因为j在上一次关于j的小循环跳出后未发生改变，而arr[j]的值已经移到了之前第7步结束时arr[i]的位置)
 * 9、一直执行循环直到跳出大while循环，即i>=j;
 * 10、此时将枢轴temp的值放到arr[i]中，结束
 * 
 * 当然有时候枢轴的选取不一定是在数组的第一个值作为枢轴，这个时候只需要从顺序表中找到枢轴将其和第一个元素交换即可（方法类似于顺序表找最值）
 * 
 * */
//这个是属于最简单的一种划分，即枢轴在顺序表的第一个且以枢轴作为比较元素进行划分，其余的方法都是从该方法衍生出来的。
void partition(int arr[], int length)
{
    int temp;
    int i = 0, j = length - 1;
    temp = arr[i];
    while (i < j)
    {
        while (i < j && arr[j] >= temp)
        {
            --j;
        }
        if (i < j)
        {
            arr[i] = arr[j];
            i++;
        }
        while (i < j && arr[i] < temp)
        {
            i++;
        }
        if (i < j)
        {
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = temp;
}
//下面是万能方法：arr表示顺序表的数组，length表示顺序表长度，k表示枢轴在顺序表的位置，comp表示比较元素
//于是代码比较简单了，只是比较元素换成了comp而已，对于大部分的顺序表划分问题都可以通过这个函数进行修改写出来
void partition (int arr[],int length,int comp,int k)
{
    int temp;//用来临时存储枢轴的值
    int i = 0, j = length - 1;//i,j分别指向顺序表的第一个和最后一个
    temp = arr[k];
    arr[k] = arr[0];
    arr[0] = temp;
    //这几步分别是将枢轴元素拿到数组的第一个
    
    while(i<j)
    {
        while(i<j&&arr[j]>=comp)
        {
            j--;
        }
        if(i<j)
        {
            arr[i] = arr[j];
            i++;
        }
        while(i<j&&arr[i]<=comp)
        {
            i++;
        }
        if(i<j)
        {
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = temp;
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

    /*
    int a[5] = {3, 4, 9, 1, 5};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, arrLength);
    for (int i = 0; i < length; i++)
    {
        printf("%d \t", data[i]);
    }
    printf("\n");
    reverse(data, &arrLength, 1, 4);
    for (int i = 0; i < length; i++)
    {
        printf("%d \t", data[i]);
    }
    */

    /*取最大值和最小值
    int a[5] = {3, 4, 9, 1, 5};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, arrLength);
    int maxIdx = 0;
    int minIdx = 0;
    int max=getMaxElem(data, &arrLength, &maxIdx);
    int min=getMinElem(data, &arrLength, &minIdx);
    printf("max: %d,maxIndex:%d", max, maxIdx);
    printf("min: %d,minIdx:%d", min, minIdx);
    */

    /*顺序表归并
    int a[5] = {1, 4, 7, 10, 12};
    int aLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, aLength);

    int b[10] = {1, 6, 9, 14, 17, 19, 25, 27, 33, 38};
    int bLength = sizeof(b) / sizeof(b[0]);
    createSqList(data, &length, a, bLength);

    for (int i = 0; i < aLength; i++)
    {
        printf("%d \t", a[i]);
    }
    printf("\n");
    for (int i = 0; i < bLength; i++)
    {
        printf("%d \t", b[i]);
    }
    printf("\n");

    int c[100] = {};
    mergeArray(a, aLength, b, bLength, c);
    for (int i = 0; i < aLength + bLength; i++)
    {
        printf("%d \t", c[i]);
    }
    */
    int a[7] = {2, 1, -7, -3, 5, 6, -1};
    int aLength = sizeof(a) / sizeof(a[0]);
    createSqList(data, &length, a, aLength);
    for (int i = 0; i < length; i++)
    {
        printf("%d \t", data[i]);
    }
    printf("\n");
    partition(data, length);
    for (int i = 0; i < length; i++)
    {
        printf("%d \t", data[i]);
    }
    getchar();
    getchar();
    return 0;
}