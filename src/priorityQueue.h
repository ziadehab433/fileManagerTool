#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include "PROCESS.h"

typedef struct QueueNode2
{
    Process entry;
    struct QueueNode2 * next;
}QueueNode2;

typedef struct
{
    QueueNode2 * front;
    QueueNode2 * rear;
    int size;
}Queue2;

void CreateQueue2(Queue2 * pq);
int QueueEmpty2(Queue2 * pq);
int QueueFull2(Queue2 * pq);
void Enqueue2(Queue2 * pq, Process e);
void Dequeue2(Queue2 * pq, Process * pe);
void TraverseQueue2(Queue2 * pq , void (*pf)(Process));
void SwapFrontRear2(Queue2 * pq);
void AppendQueue2(Queue2 * pq1 , Queue2 * pq2);
int QueueSize2(Queue2 * pq);


int checkDuplicateProcess2(Queue2* pq, int processID);


#endif // PRIORITYQUEUE_H_INCLUDED
