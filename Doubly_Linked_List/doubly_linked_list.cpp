#include <iostream>
using namespace std;

typedef struct DLNode
{
    int data;
    struct DLNode *prior;
    struct DLNode *next;
} DLNode;

//双链表元素的插入
void insertElem(DLNode *&p, DLNode *&s)
{
    cout << "原来p节点next指针" << p->next << endl;
    cout << "原来p节点prior指针" << p->prior << endl;
    cout << "原来s节点next指针" << s->next << endl;
    cout << "原来s节点prior指针" << s->prior << endl;
    //主体部分
    s->next = p->next;
    s->prior = p;
    s->next->prior = s;
    p->next = s;
    //主体部分
    cout << "insert success!" << endl;
    cout << "现在p节点next指针" << p->next << endl;
    cout << "现在p节点next指针" << p->prior << endl;
    cout << "现在s节点next指针" << s->next << endl;
    cout << "现在s节点prior指针" << s->prior << endl;
}

//双链表元素的删除
//已知 要删除节点 s   s的前驱节点p
void deleteElem(DLNode *&p, DLNode *&s)
{
    p->next = s->next;
    s->next->prior = p;
    free(s);
}
//已知 要删除节点 s
void deleteElem(DLNode *&s)
{
    cout << "原来p节点next指针" << s->prior->next << endl;
    cout << "原来p节点prior指针" << s->prior->prior << endl;
    //函数主体
    s->prior->next = s->next;
    s->next->prior = s->prior;
    free(s);
    //函数主体
    cout << "delete success!" << endl;
}

int main()
{
    DLNode *head = (DLNode *)malloc(sizeof(DLNode));
    head->data = 1;
    head->prior = NULL;
    head->next = NULL;
    DLNode *p = (DLNode *)malloc(sizeof(DLNode));
    p->data = 111;
    p->next = NULL;
    p->prior = head;

    head->next = p;
    DLNode *s = (DLNode *)malloc(sizeof(DLNode));
    s->data = 19990519;
    s->prior = NULL;
    s->next = NULL;
    insertElem(head, s);

    deleteElem(s);
    cout << "现在头结点next指针" << head->next << endl;
    cout << "现在头结点prior指针" << head->prior << endl;
    getchar();
    return 0;
}