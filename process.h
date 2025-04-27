#ifndef PCB_H
#define PCB_H

typedef struct {
    int processID;
    char state[20];
    int priority;
    int programCounter;
    int memoryLowerBound;
    int memoryUpperBound;
} PCB;

PCB createPCB(int id, int lowerBound, int upperBound, int priority);
void updateProcessState(PCB* pcb, const char* newState);
void printPCB(const PCB* pcb);

#endif // PCB_H
