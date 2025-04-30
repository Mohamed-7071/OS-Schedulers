#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== Queue ====================

Node* readyQueue = NULL;

void enqueue(PCB newProcess) {
    Node* node=(Node*)malloc(sizeof(Node));
    if(!node){
        return;
    }

    node->process=newProcess;
    node->next=NULL;

    if (readyQueue== NULL)
    {
        readyQueue=node;
    }else{
        Node* temp =readyQueue;
        while (temp->next)
        {
            temp=temp->next;
        }
        temp->next=node;   
    }
}

PCB dequeue(){
    PCB x;
    if (readyQueue==NULL)
    {
        printf("Queue's empty\n");

        return x;
    }

    Node* front=readyQueue;

    PCB toreturn=front->process;
    readyQueue=front->next;
    free(front);
    return toreturn;
}
int isQueueEmpty() {
    return (readyQueue == NULL); 
}

// ==================== FCFS SCHEDULER ====================
void runFCFS() {
    printf("\n=== Running in First-Come First-Served Mode ===\n");

    while (!isQueueEmpty()) {
        PCB current = dequeue();

        updateProcessState(&current, RUNNING);
        printf(">> Now running process #%d\n", current.processID);

        // Simulating execution. Not super exciting.
        while (current.programCounter <= current.memoryUpperBound) {
            printf("  -> Executing at PC=%d\n", current.programCounter);
            current.programCounter++;
        }

        updateProcessState(&current, EXIT);
        printf(">> Finished process #%d\n\n", current.processID);
    }

}

// ==================== ROUND ROBIN SCHEDULER ====================

void runRoundRobin(int quantum) {
    printf("\n=== Round Robin Scheduling ===\n");
    while (!isQueueEmpty()) {

        PCB p=dequeue();
        updateProcessState(&p, RUNNING);
        printf("[Running Process] ID: %d\n", p.processID);
        int steps = 0;
        while (steps < quantum && p.programCounter <= p.memoryUpperBound) {
            printf("Executing instruction at PC = %d\n", p.programCounter);
            p.programCounter++;
            steps++;
        }

    if (p.programCounter > p.memoryUpperBound) {
            updateProcessState(&p, EXIT);
            printf("[Process Completed] ID: %d\n\n", p.processID);
        } else {
            updateProcessState(&p, READY);
            enqueue(p);
        }
    }


}
// ==================== MLFQ SCHEDULER ====================

Node* queues[4] = {NULL, NULL, NULL, NULL};
int quantums[4] = {1, 2, 4, 8};  // quantum doubles per level

void enqueueToLevel(PCB process, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;

    if (queues[level] == NULL) {
        queues[level] = newNode;
    } else {
        Node* temp = queues[level];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void runMultilevelFeedback() {
    printf("\n=== Multilevel Feedback Queue Scheduling ===\n");

    // While any queue has processes
    while (queues[0] || queues[1] || queues[2] || queues[3]) {
        for (int level = 0; level < 4; level++) {
            while (queues[level]) {
                // Remove first process from current level queue
                Node* node = queues[level];
                PCB p = node->process;
                queues[level] = node->next;
                free(node);

                updateProcessState(&p, RUNNING);
                printf("[Running P%d] Priority: %d (Queue %d)\n", p.processID, p.priority, level);

                int steps = 0;
                int q = quantums[level];

                while (steps < q && p.programCounter <= p.memoryUpperBound) {
                    printf("Executing P%d: PC = %d\n", p.processID, p.programCounter);
                    p.programCounter++;
                    steps++;
                }

                if (p.programCounter > p.memoryUpperBound) {
                    updateProcessState(&p, EXIT);
                    printf("[P%d Completed]\n", p.processID);
                } else {
                    updateProcessState(&p, READY);
                    int nextLevel = (level < 3) ? level + 1 : 3;
                    enqueueToLevel(p, nextLevel);
                    printf("[P%d Demoted to Queue %d]\n", p.processID, nextLevel);
                }
            }
        }
    }
}



