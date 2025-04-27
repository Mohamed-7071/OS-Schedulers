#ifndef PROCESS_H
#define PROCESS_H

/* Kick off a new process: filename → memory, at given arrivalTime */
void createProcess(const char *filename, int arrivalTime);

/* Load program lines into memory; returns how many lines written */
int loadProgram(const char *filename, int memoryStartIndex);

/* Write the 5 PCB fields directly into memory */
void initializePCB(int pid,
                   int memLower, int memUpper,
                   int priority,
                   int pcbStartIndex);

/* (Stub for future) parse one instruction */
void parseInstruction(char *instructionLine, int processId);

#endif /* PROCESS_H */
