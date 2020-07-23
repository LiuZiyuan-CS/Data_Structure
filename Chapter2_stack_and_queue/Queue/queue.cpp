#include <stdio.h>
#include <stdlib.h>

#define maxSize 50

int isEmpty(int queue[], int front, int rear)
{
    if (front == rear)
        return 1; //队空
    else
        return 0; //队没空
}

int isFull(int queue[], int front, int rear)
{
    if (front == (rear + 1) % maxSize)
        return 1; //队满
    else
        return 0; //队未满
}

int enQueue(int queue[], int *front, int *rear, int elem)
{
    if (isFull(queue, *front, *rear) == 1)
        return 0; //队满无法操作
    else
    {
        *rear = ((*rear) + 1) % maxSize;
        queue[*rear] = elem;
        return 1;
    }
}

int dequeue(int queue[], int *front, int *rear)
{
    if (isEmpty(queue, *front, *rear) == 1)
        return 0; //队空
    else
    {
        *front = ((*front) + 1) % maxSize;
        int elem = queue[*front];
        return 1;
    }
}

int main()
{
    int queue[maxSize] = {NULL, 2, 3, 4, 5};
    int front = 0, rear = 4;

    enQueue(queue, &front, &rear, 5);
    for (int i = front + 1; i <= rear; i++)
    {
        printf("%d", queue[i]);
    }

    printf("\n");
    printf("%d", front);
    
    printf("\n");
    printf("%d", rear);

    getchar();
    return 0;
}
