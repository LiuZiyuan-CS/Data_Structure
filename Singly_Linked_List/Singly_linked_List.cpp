#include <iostream>
using namespace std;

typedef struct LNode
{
    int data;           //数据域
    struct LNode *next; //指向下一个节点的指针
} LNode,*SinglyLinkedList;

/*单链表初始化*/
void init(SinglyLinkedList singlyLinkedList)
{
    singlyLinkedList = (LNode *)malloc(sizeof(LNode));
    singlyLinkedList->next = NULL;
}

/*单链表元素插入*/
void insertElm(LNode *&p, LNode *&s)
{
    cout<<"原来p节点next指针"<< p->next << endl;
    s->next = p->next;
    p->next = s;
    cout << "insert success!" << endl;
    cout<<"现在p节点next指针"<< p->next << endl;
}

/*单链表元素删除*/
void deleteElm(LNode *&p, LNode *&s)
{
    cout<<"原来p节点next指针"<< p->next << endl;
    //函数主体部分，其余的都是测试用的语句
    p->next = s->next;
    free(s);
    //函数主体部分
    s->next = NULL;
    cout << "delete success!" << endl;
    cout<<"现在p节点next指针"<< p->next << endl;
}

int main()
{
    LNode *head = (LNode *)malloc(sizeof(LNode));
    head->data = 1;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = 19990519;
    insertElm(head, s);
    cout << head->next->data << endl;
    cout << "s Address\t" << s->next << endl;
    deleteElm(head, s);
    cout << s << endl;
    getchar();
    return 0;
}