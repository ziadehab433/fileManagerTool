#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "PROCESS.h"
#include "priorityQueue.h"
#include <stdio.h>

void printEMess(){
        printf("\nWrong input! Please enter a positive number : ");
}

int checkInput() {
    int c;
    while (1) {
        if (scanf("%d", &c) != 1 || c <= 0) {
                printEMess();
            while (getchar() != '\n') {}
        } else {
            break;
        }
    }
    return c;
}

//int isValidInput(int i) {
//    if (i <= 0 || !isdigit(i)) {
//        return 0;
//    } else {
//        return 1;
//    }
//}
//

Process getProcess() {
    Process newProcess;

    printf("\nEnter process ID: ");
    newProcess.process_id=checkInput();

    printf("\nEnter burst time: ");
    newProcess.burst_time=checkInput();

    printf("\nEnter priority: ");
    newProcess.priority=checkInput();
    printf("\n");

    return newProcess;

}



int addProcess(Queue* q, Queue2* pq) {
   Process p = getProcess();
   // removed the second checkDuplicateProcess
    if (checkDuplicateProcess(q, p.process_id)) {
        return 0;
    }

    Enqueue(q, p);
    Enqueue2(pq, p);
    return 1;
}


void displayNumber(Queue* q){
    int size = QueueSize(q);
    if(size != 0){
        printf("number of waiting processes is %d \n", size);
    }else{
        printf("no waiting processes at the moment \n");
    }
}


void displayTotalBrustTime(Queue2 * pq){
    int CurrentTime = 0;
    Process CurrentProcess;
    int Qsize = QueueSize2(pq);

    if(Qsize == 0){ 
        printf("cannot calculate burst time (no processes available) \n");
        return;
    }

    Process pArr[Qsize];
    for(int i = 0; i < Qsize; i++){
       Dequeue2(pq, &CurrentProcess);
       CurrentTime = CurrentTime + CurrentProcess.burst_time;
       pArr[i] = CurrentProcess;
    }

    for(int i = 0; i < Qsize; i++){
       Enqueue2(pq, pArr[i]);
    }

    printf("The Total Amount Of Cpu Burst Time is %d seconds \n", CurrentTime);
}


void Display(Process p) {
   printf("\n Process Id : %i , burst time %i , pirority %i \n",p.process_id,p.burst_time , p.priority);

}

void displayInputOrder(Queue * q)
{
    if(QueueEmpty(q))
        printf("\nThere is No Process ! \n");
    else
        TraverseQueue(q,Display);
}

void displayServedOrder(Queue2 * q)
{
    if(QueueEmpty2(q))
        printf("\nThere is No Process ! \n");
    else
        TraverseQueue2(q,Display);
}

void serveProcces(Queue2*pq,Queue*q)
{
    Process p;

    Dequeue2(pq,&p);
    int id = p.process_id;
    DequeueAtID(q,id);

}


void save_to_file(Queue *regular_queue) {
    FILE *file = fopen("processes.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Process ID\tBurst Time\tPriority\n");

    if(QueueEmpty(regular_queue))
        printf("\nchanges saved successfully \n");
    else{

        Process process;
        while (!QueueEmpty(regular_queue)) {
            Dequeue(regular_queue, &process);
            fprintf(file, "%d\t\t%d\t\t%d\n", process.process_id, process.burst_time, process.priority);
        }


        fclose(file);
        printf("Processes saved to 'processes.txt'\n");
   }
}


void load_from_file(Queue2* priority_queue, Queue* regular_queue) {
    FILE *file = fopen("processes.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char buffer[100];

    // to skip the header
    fgets(buffer, sizeof(buffer), file);

    Process process;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d %d %d", &process.process_id, &process.burst_time, &process.priority);

        Enqueue2(priority_queue, process);
        Enqueue(regular_queue, process);
    }

    fclose(file);
    printf("Processes loaded from 'processes.txt'\n");
}

int main() {
    Queue q;
    CreateQueue(&q);

    Queue2 pq;
    CreateQueue2(&pq);

    load_from_file(&pq, &q);

    int choice;
    do {
        printf("\n----- MENU -----\n");
        printf("1. Add a process\n");
        printf("2. Serve a process\n");
        printf("3. Display the number of processes waiting\n");
        printf("4. Display the input order of processes\n");
        printf("5. Display the served order of processes\n");
        printf("6. Display the total burst time\n");
        printf("7. Exit (Save in a file)\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nWrong input! Please enter a number.\n");
            scanf("%*s");
            continue;
        }

        printf("\n");

        switch (choice) {
            case 1:
               if( addProcess(&q, &pq))
                    printf("\nProcess Added Successfully \n");
               else
                    printf("\nProcess with this ID  already exists. Not adding.\n");
               break;
            case 2:
                if(QueueEmpty2(&pq))
                    printf("\nthere is no process to serve !\n");
                else{
                    serveProcces(&pq,&q);
                    printf("\nthe procces has served successfully\n");
                }
                break;
            case 3:
                displayNumber(&q);
                break;
            case 4:
                displayInputOrder(&q);
                break;
            case 5:
                displayServedOrder(&pq);
                break;
            case 6:
                displayTotalBrustTime(&pq);
                break;
            case 7:
                save_to_file(&q);
                exit(0);
            default:
                printf("\nWrong choice, Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

