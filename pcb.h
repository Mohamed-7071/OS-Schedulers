#ifndef PCB_H
#define PCB_H

typedef enum ProcessState {
    NEW,     
    READY,   
    RUNNING, 
    BLOCKED,  
    EXIT      
} ProcessState;


typedef struct PCB {
    int processID;         
    ProcessState state;    
    int priority;          
    int programCounter;    
    int memoryLowerBound; 
    int memoryUpperBound;  
} PCB;


PCB createPCB(int id, int lowerBound, int upperBound, int priority);
void updateProcessState(PCB *pcb, ProcessState newState);
void printPCB(const PCB *pcb);

#endif // PCB_H
