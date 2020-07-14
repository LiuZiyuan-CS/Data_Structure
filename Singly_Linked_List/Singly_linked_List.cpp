/**
 * 1、头尾插法建表
 * 2、链表结点插入和删除
 * 3、链表的逆置
 * 4、取最值
 * 5、顺序归并和逆序归并
 * */

#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
    int data;           //数据域
    struct LNode *next; //指向下一个节点的指针
} LNode;

/*
尾插法建立单链表：通过键盘键入数据
PS：注意二级指针的问题，不要遗漏括号
*/
void createLinListR(LNode **head)
{
    *head = (LNode *)malloc(sizeof(LNode));
    (*head)->data = NULL;
    (*head)->next = NULL;
    LNode *p = NULL;    //存放需要插入数据的节点指针
    LNode *r = (*head); //始终指向尾结点的指针
    int length;         //需要插入的节点个数
    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p->next = NULL;
        scanf("%d", &(p->data));
        p->next = r->next;
        r->next = p;
        r = p;
    }
}
/*
尾插法建立单链表：通过传入数组来传入数据
head:头结点的二级指针
data[]：包含输入数据的数组
arrLength：data[]的长度，因为函数调用时是只引用数组指针，所以必须在函数体外先计算好data[]数组的长度
            数组长度的具体的计算方法：int arrLength = sizeof(a) / sizeof(a[0]);
*/
void createLinListR(LNode **head, int data[], int arrLength)
{
    (*head) = (LNode *)malloc(sizeof(LNode)); //取head指针本身，这里不是二级指针，注意括号问题。不然会报错
    (*head)->data = NULL;
    (*head)->next = NULL;
    LNode *p = NULL;    //存放需要插入数据的节点指针
    LNode *r = (*head); //始终指向尾结点的指针
    for (int i = 0; i < arrLength; i++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p->next = NULL;
        p->data = data[i];
        p->next = r->next;
        r->next = p;
        r = p;
    }
}

/*头插法创建单链表：通过传入数组来传入数据*/
void createLinkListH(LNode **head, int data[], int arrLength)
{
    (*head) = (LNode *)malloc(sizeof(LNode *));
    (*head)->data = NULL;
    (*head)->next = NULL;
    LNode *p = NULL;
    for (int i = 0; i < arrLength; i++)
    {
        p = (LNode *)malloc(sizeof(LNode *));
        p->next = NULL;
        p->data = data[i];
        p->next = (*head)->next;
        (*head)->next = p;
    }
}
/*头插法创建单链表：键盘传入数据*/
void createLinkListH(LNode **head)
{
    (*head) = (LNode *)malloc(sizeof(LNode *));
    (*head)->data = NULL;
    (*head)->next = NULL;
    LNode *p = NULL;
    int n; //插入的数据个数
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        p = (LNode *)malloc(sizeof(LNode *));
        p->next = NULL;
        scanf("%d", &(p->data));
        p->next = (*head)->next;
        (*head)->next = p;
    }
}

/*
单链表元素插入
p：插入位置的前驱节点
s：插入的节点
*/

void insertElem(LNode **p, LNode *s)
{
    s->next = (*p)->next;
    (*p)->next = s;
}

/**
单链表元素删除
p:被删除节点的前驱节点
s：被删除的节点
*/
void deleteElem(LNode **p, LNode *s)
{
    (*p)->next = s->next;
    free(s);
    s->next = NULL;
}

/**
 * 单链表逆置
 * 从p节点到q节点转置
 * */
void reverse(LNode **p, LNode **q)
{
    LNode *t;
    while ((*p)->next != (*q))
    {
        t = (*p)->next;
        (*p)->next = t->next;
        t->next = (*q)->next;
        (*q)->next = t;
    }
}

/**
 * 取最大值
 * */
int getMaxElem(LNode *head)
{
    LNode *p, *q;               //p当前循环的节点，q表示当前找到的拥有最大值的节点
    int max = head->next->data; //max表示当前的最大值
    q = p = head->next;         //初始化时将p，q分别记为开始节点
    while (p != NULL)
    {
        if ((p->data) > max)
        {
            max = p->data;
            q = p;
        }
        p = p->next;
    }
    return max;
}

/**
 * 取最小值,与最大值类似，原理不再赘述
 * */
int getMinElem(LNode *head)
{
    LNode *p, *q;
    int min = head->next->data;
    q = p = head->next;
    while (p != NULL)
    {
        if ((p->data) < min)
        {
            min = p->data;
            q = p;
        }
        p = p->next;
    }
    return min;
}

/**
 * 链表的归并 （采用的尾插法）
 * ps：A，B均是已排序好的链表，此方法无需申请新的空间，利用A或B的任一头结点作为C的头结点即可
 * A:需要归并的链表A  
 * B:需要归并的链表B
 * C:归并后的新链表C
 * 依次比较A，B两个链表的当前节点的大小，将较小的节点先放入C，当A,B其中一个链表归并结束，余下的另一条链表剩余节点直接接入C的最后一个节点即可
 * */
void merge(LNode *A, LNode *B, LNode **C)
{
    LNode *p = A->next; //p表示A链表未归并部分的第一个节点
    LNode *q = B->next; //q表示B链表未归并部分的第一个节点
    LNode *r;           //r表示C链表的尾结点
    (*C) = A;
    (*C)->next = NULL;
    free(B);
    r = (*C);
    while (p!= NULL && q != NULL)   //注意不是 p->next 和 q->next 为NULL时跳出循环，是本身为空时跳出循环
    {
        if (p->data <= q->data)
        {
            r->next = p; //p节点接到C链表来
            p = p->next; //将p移到下一个节点处
            r = r->next; //将r移到下一个
        }
        else
        {
            r->next = q;
            q = q->next;
            r = r->next;
        }
    }
    if(p!=NULL) //此时B链表已被归并完毕，A链表余下的部分接到C的尾部
    {
        r->next = p;
    }
    if(q!=NULL)
    {
        r->next = q;
    }
}

/**
 * 链表的归并 （采用的头插法，这样可以实现链表的逆排序）
 * ps：A，B均是已排序好的链表，此方法无需申请新的空间，利用A或B的任一头结点作为C的头结点即可
 * A:需要归并的链表A  
 * B:需要归并的链表B
 * C:归并后的新链表C
 * 依次比较A，B两个链表的当前节点的大小，将较小的节点先放入C的开始节点，
 * 当A,B其中一个链表归并结束，余下的另一条链表按头插法的方法插入到C链表中
 * */
void mergeReverse(LNode *A,LNode *B,LNode **C)
{
    LNode *p = A->next; //p表示A链表未归并部分的第一个节点
    LNode *q = B->next; //q表示B链表未归并部分的第一个节点
    LNode *s;           //s指向当前p与q中数据域较小的那个节点。
    (*C) = A;           
    (*C)->next = NULL;
    free(B);
    while(p!=NULL && q!=NULL) 
    {
        if(p->data<=q->data)
        {
            s = p;              //s指向p的当前节点结点
            p = p->next;        //p指向p的后继节点
            //“头插法插入s节点”
            s->next = (*C)->next;
            (*C)->next = s;
        }
        else
        {
            //if条件块中的相类似，不再赘述
            s = q;
            q = q->next;
            s->next = (*C)->next;
            (*C)->next = s;
        }
    }
    //此处与之前的顺序归并不同，这里需要哪个链表还有剩余结点。然后将剩余结点采用头插法的形式插入到C链表中 
    while(p!=NULL)
    {
        s = p;
        p = p->next;
        s->next = (*C)->next;
        (*C)->next = s;
    }
    while(q!=NULL)
    {
        s = q;
        q = q->next;
        s->next = (*C)->next;
        (*C)->next = s;
    }
}

int main()
{
    /* 使用带数组的尾插法创建单链表
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinListR(&head, a,arrLength);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /*使用键盘输入尾插法创建单链表
    LNode *head;
    createLinListR(&head);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /* 使用带数组的头插法创建单链表
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinkListH(&head, a,arrLength);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /*使用键盘输入头插法创建单链表
    LNode *head;
    createLinkListH(&head);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /*插入元素
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinListR(&head, a,arrLength);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    printf("\n");
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = 990519;
    s->next = NULL;
    insertElem(&head, s);
    p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    */

    /*删除元素
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinListR(&head, a, arrLength);
    LNode *p = head->next;
    while (p != NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    printf("\n");
    LNode *s = head->next;
    deleteElem(&head, s);
    p = head->next;
    while (p != NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /* 逆置单链表   
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinkListH(&head, a, arrLength);
    LNode *p = head->next;
    LNode *r = NULL;
    while (p != NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        if (p->next == NULL){
            r = p;
        }
        p = p->next;
    }
    reverse(&(head->next), &(r));
    p = head->next;
    while (p != NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    getchar();
    */

    /*查找单链表的最大值和最小值
    LNode *head;
    int a[5] = {10, 5, 2, 8, 7};
    int arrLength = sizeof(a) / sizeof(a[0]);
    createLinkListH(&head, a,arrLength);
    LNode *p = head->next;
    while (p!= NULL)
    {
        printf("data: %d \n", (p->data));
        printf("next: %d\n", (p->next));
        p = p->next;
    }
    int max=getMaxElem(head);
    printf("%d", max);
    int min = getMinElem(head);
    printf("\n");
    printf("%d", min);
    getchar();
    */

    /*
    LNode *A;
    LNode *B;
    LNode *C;
    int a[9] = {2, 6, 9, 13, 17,24,55,67,89};
    int b[5] = {1, 4, 8, 15, 24};
    int arrLength_a = sizeof(a) / sizeof(a[0]);
    int arrLength_b = sizeof(b) / sizeof(b[0]);
    createLinListR(&A, a,arrLength_a);
    createLinListR(&B, b,arrLength_b);
    LNode *p = A->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    p = B->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    printf("\n");
    merge(A, B, &C);
    p = C->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    getchar();
    */

    LNode *A;
    LNode *B;
    LNode *C;
    int a[9] = {2, 6, 9, 13, 17,24,55,67,89};
    int b[5] = {1, 4, 8, 15, 24};
    int arrLength_a = sizeof(a) / sizeof(a[0]);
    int arrLength_b = sizeof(b) / sizeof(b[0]);
    createLinListR(&A, a,arrLength_a);
    createLinListR(&B, b,arrLength_b);
    LNode *p = A->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    p = B->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    printf("\n");
    mergeReverse(A, B, &C);
    p = C->next;
    while (p!= NULL)
    {
        printf("next: %d,data: %d \n", (p->next),(p->data));
        p = p->next;
    }
    getchar();

    return 0;
}