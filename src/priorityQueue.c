#include "priorityQueue.h"
#include <stdlib.h>
void CreateQueue2(Queue2 * pq)
{
    pq->front = NULL;
    pq->rear = NULL;
    pq->size = 0;
}
int QueueEmpty2(Queue2 * pq)
{
    return pq->size == 0;
}
int QueueFull2(Queue2 * pq)
{
    return 0;
}
void Enqueue2(Queue2 * pq, Process e)
{
    QueueNode2 * pn = (QueueNode2 *)malloc(sizeof(QueueNode2));
    pn->entry = e;
    pn->next = NULL;

    if(pq->front == NULL){
        pq->rear = pn;
        pq->front = pn;
    }else if(pq->front->entry.priority > pn->entry.priority){
        pn->next = pq->front;
        pq->front = pn;
    }else{
        QueueNode2* p = pq->front;
        while(p){
            if(p->next != NULL && p->next->entry.priority <= pn->entry.priority){
                p = p->next;
                continue;
            }
            pn->next = p->next;
            p->next = pn;
            break;
        }
    }

    pq->size++;
}
void Dequeue2(Queue2 * pq, Process * pe)
{
    QueueNode2 * pn = pq->front;
    *pe = pn->entry;
    pq->front = pq->front->next;
    free(pn);
    if(pq->front == NULL)
        pq->rear = NULL;
    pq->size --;
}

void TraverseQueue2(Queue2 * pq , void (*pf)(Process))
{
    QueueNode2 * pn = pq->front;
    while(pn)
    {
        (*pf)(pn->entry);
        pn = pn->next;
    }
}

void DestroyQueue2(Queue2 *pq)
{
    while(pq->front)
    {
        pq->rear = pq->front->next;
        free(pq->front);
        pq->front = pq->rear;
    }
    pq->size = 0;
}

void SwapFrontRear2(Queue2 * pq)
{
    if(pq->front != pq->rear)
    {
        QueueNode2 * pn = pq->front;
        while(pn->next->next != NULL)
            pn = pn->next;
        pq->rear->next = pq->front->next;
        pq->front->next = NULL;
        pn->next = pq->front;
        pn = pq->rear;
        pq->rear = pq->front;
        pq->front = pn;
    }

}

void AppendQueue2(Queue2 * pq1 , Queue2 * pq2)
{
    QueueNode2 * pn = pq2->front;
    while(pn)
    {
        QueueNode2 * N = (QueueNode2 *)malloc(sizeof(QueueNode2));
        N->entry = pn->entry;
        N->next = NULL;
        pq1->rear->next = N;
        pq1->rear = N;
        pn = pn->next;
        pq1->size++;
    }
}

//  check if  processID is already exists
int checkDuplicateProcess2(Queue2* pq, int processID) {
    QueueNode2 *current = pq->front;
    while (current != NULL) {
        if (current->entry.process_id == processID) {
            return 1;
        }
        current = current->next;
    } return 0;
    }


int QueueSize2(Queue2 * pq){
    return pq->size;
}

