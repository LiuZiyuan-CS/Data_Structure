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
 * 单链表转置
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
    return 0;
}