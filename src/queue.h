#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "PROCESS.h"
typedef struct queuenode
{
    Process entry;
    struct queuenode * next;
}QueueNode;

typedef struct
{
    QueueNode * front;
    QueueNode * rear;
    int size;
}Queue;

void CreateQueue(Queue * pq);
int QueueEmpty(Queue * pq);
int QueueFull(Queue * pq);
void Enqueue(Queue * pq, Process e);
void Dequeue(Queue * pq, Process * pe);
void DequeueAtID(Queue * pq,int ID);
void TraverseQueue(Queue * pq , void (*pf)(Process));
void SwapFrontRear(Queue * pq);
void AppendQueue(Queue * pq1 , Queue * pq2);
int QueueSize(Queue * pq);

int checkDuplicateProcess(Queue* q,  int processID);

#endif // QUEUE_H_INCLUDED
