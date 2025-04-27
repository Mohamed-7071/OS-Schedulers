/* pcb.c */
#include "pcb.h"
#include <stdio.h>
#include <string.h>

// String representations of ProcessState for printing
static const char *stateNames[] = {
    "NEW",
    "READY",
    "RUNNING",
    "BLOCKED",
    "EXIT"
};

PCB createPCB(int id, int lowerBound, int upperBound, int priority) {
    PCB pcb;
    pcb.processID = id;
    pcb.state = NEW;
    pcb.priority = priority;
    pcb.programCounter = lowerBound;
    pcb.memoryLowerBound = lowerBound;
    pcb.memoryUpperBound = upperBound;
    return pcb;
}

 void updateProcessState(PCB *pcb, ProcessState newState) {
    pcb->state = newState;
}

void printPCB(const PCB *pcb) {
    printf("PCB Details:\n");
    printf("Process ID: %d\n", pcb->processID);
    printf("State: %s\n", stateNames[pcb->state]);
    printf("Priority: %d\n", pcb->priority);
    printf("Program Counter: %d\n", pcb->programCounter);
    printf("Memory Lower Bound: %d\n", pcb->memoryLowerBound);
    printf("Memory Upper Bound: %d\n", pcb->memoryUpperBound);
}
