#include "queue.h"
#include <stdlib.h>

void CreateQueue(Queue * pq)
{
    pq->front = NULL;
    pq->rear = NULL;
    pq->size = 0;
}
int QueueEmpty(Queue * pq)
{
    return pq->size == 0;
}
int QueueFull(Queue * pq)
{
    return 0;
}
void Enqueue(Queue * pq, Process e)
{
    QueueNode * pn = (QueueNode *)malloc(sizeof(QueueNode));
    pn->entry = e;
    pn->next = NULL;
    if(pq->front == NULL)
        pq->front = pn;
    else
        pq->rear->next = pn;
    pq->rear = pn;
    pq->size ++;
}
void Dequeue(Queue * pq, Process * pe)
{
    QueueNode * pn = pq->front;
    *pe = pn->entry;
    pq->front = pq->front->next;
    free(pn);
    if(pq->front == NULL)
        pq->rear = NULL;
    pq->size --;

}

void DequeueAtID(Queue* q, int ID){ 
    if(q->front == NULL){ 
        return;
    }

    q->size--;

    QueueNode *pn = q->front;
    QueueNode *tmp = NULL;
    while(pn != NULL){ 
        if(pn->entry.process_id == ID){ 
            break;
        }
        tmp = pn;
        pn = pn->next;
    }

    if(tmp == NULL){ 
        tmp = q->front;
        
        if(q->front->next == NULL){ 
            q->rear = NULL;
        }

        q->front = q->front->next;
        free(tmp);
        return;
    }

    tmp->next = pn->next;
    if(pn->next == NULL){ 
        q->rear = tmp;
    }

    free(pn);
    return;
}

void TraverseQueue(Queue *pq, void (*pf)(Process)) {
    QueueNode *pn = pq->front;
    while (pn) {
        (*pf)(pn->entry);
        pn = pn->next;
    }
}


void DestroyQueue(Queue *pq)
{
    while(pq->front)
    {
        pq->rear = pq->front->next;
        free(pq->front);
        pq->front = pq->rear;
    }
    pq->size = 0;
}

void SwapFrontRear(Queue * pq)
{
    if(pq->front != pq->rear)
    {
        QueueNode * pn = pq->front;
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

void AppendQueue(Queue * pq1 , Queue * pq2)
{
    QueueNode * pn = pq2->front;
    while(pn)
    {
        QueueNode * N = (QueueNode *)malloc(sizeof(QueueNode));
        N->entry = pn->entry;
        N->next = NULL;
        pq1->rear->next = N;
        pq1->rear = N;
        pn = pn->next;
        pq1->size++;
    }
}



//  check if  processID is already exists
int checkDuplicateProcess(Queue* q, int processID) {
    QueueNode *current = q->front;
    while (current != NULL) {
        if (current->entry.process_id == processID) {
            return 1;
        }
        current = current->next;
    } return 0;
}

int QueueSize(Queue * pq){
    return pq->size;
}
