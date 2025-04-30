

#ifndef  SCHEDULER_H
#define SCHEDULER_H

#include "pcb.h"

typedef struct Node
{
    PCB process;
    struct Node* next;
}Node;

extern Node* readyQueue;

void enqueue(PCB process);
PCB dequeue();
int isQueueEmpty();


void runFCFS();               
void runRoundRobin(int quantum); 
void runMultilevelFeedback(); 

#endif



