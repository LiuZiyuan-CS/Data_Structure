/**
 * 关于双链表的操作问题，这里引用天勤视频中的一道例题来实现一些双链表的相关操作
 * 例：一双链表非空，由head指针指出，结点结构为{llink,data,rlink}，请设计一个将结点数据域data值最大的那个结点找出来（最大节点只有一个）
 * 移动到链表的最前边的的算法，要求不得申请新结点
 * */
#include <stdio.h>
#include <stdlib.h>
//双链表结点结构体
typedef struct DLNode
{
    int data;
    struct DLNode *llink;
    struct DLNode *rlink;
} DLNode;

//创建一个双链表（这里采用尾插法,利用数组插入数据）
void createDoublyLinkList(DLNode **head,int data[],int dataLength)
{
    (*head) = (DLNode *)malloc(sizeof(DLNode));
    (*head)->rlink = NULL;
    (*head)->data = NULL;
    DLNode *p;
    DLNode *r;//用来指向链表的尾结点指针
    r = (*head);
    for (int i = 0; i < dataLength;i++)
    {
        p = (DLNode *)malloc(sizeof(DLNode));
        p->rlink = NULL;
        //下面四步就是对双链表进行插入的操作
        p->data = data[i];
        p->rlink = r->rlink;
        p->llink = r;
        r->rlink = p;
        //r要重新指向尾结点
        r = p;
    }
}

//实现题目的要求：找到最大值，移动到的一个
void getMaxElemPutFirst(DLNode **head)
{
    DLNode *p = (*head)->rlink, *q = p;
    int max = p->data;
    while(p!=NULL)
    {
        if(max<p->data)
        {
            max = p->data;
            q = p;
        }
        p = p->rlink;
    }
    //"删除结点q"⭐虽然描述为删除，其实是将q结点的前驱结点和后继节点连接起来
    DLNode *l = q->llink, *r = q->rlink;
    l->rlink = r;
    //如果 q结点已经是最后一个节点了那么就不需要将r结点的前驱接到l结点，因为此时r结点不存在
    if(r!=NULL){
        r->llink = l;
    }
    //将q结点插入到开始节点
    q->rlink = (*head)->rlink;
    q->rlink->llink = q;
    q->llink = (*head);
    (*head)->rlink = q;
}

int main()
{
    int data[5] = {1, 4, 9, 2, 5};
    int arrLength = sizeof(data) / sizeof(data[0]);
    DLNode *head;
    createDoublyLinkList(&head, data, arrLength);
    DLNode *p = head->rlink;
    while (p!=NULL)
    {
        printf("llink: %d \t", p->llink);
        printf("data: %d \t", p->data);
        printf("rlink: %d \t", p->rlink);
        printf("\n");
        p=p->rlink;
    }
    printf("\n");
    getMaxElemPutFirst(&head);
    p = head->rlink;
    while (p!=NULL)
    {
        printf("llink: %d \t", p->llink);
        printf("data: %d \t", p->data);
        printf("rlink: %d \t", p->rlink);
        printf("\n");
        p=p->rlink;
    }
    getchar();
    return 0;
}