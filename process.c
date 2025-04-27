/* process.c */
#include "process.h"
#include "pcb.h"
#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// change from int to string 3alashan el mem bt store only strings..momken n3ml el mem testore as objects w n3ml handle bas too much code no
static char* intToStr(int num) {
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%d", num);
    return strdup(tmp);
}

// each line takes 1 slot in memory slot
static int countLines(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    int cnt = 0;
    char line[256];
    while (fgets(line, sizeof(line), f)) cnt++;
    fclose(f);
    return cnt;
}

/* 
 * Create a new process:
 *  - figure out total size = code lines + 3 vars + 5 PCB fields 
 *  - find a free block in memory
 *  - load code, skip 3 var slots, then write PCB
 */
void createProcess(const char* filename, int arrivalTime) {
    static int nextPid = 1;
    int pid         = nextPid++;
    int nCodeLines  = countLines(filename);
    int nVars       = 3;
    int nPCBFields  = 5;
    int totalSize   = nCodeLines + nVars + nPCBFields;

    int startIndex = allocateMemory(totalSize);
    if (startIndex < 0) {
        printf("Error: not enough memory for process %d\n", pid);
        return;
    }

    int wrote = loadProgram(filename, startIndex);

    //  Reserve 3 variable slots (no writes yet) 
    int varStart = startIndex + wrote;

    // Write PCB (5 fields) 
    int pcbStart = varStart + nVars;
    int pcbEnd   = pcbStart + nPCBFields - 1;
    initializePCB(pid, startIndex, pcbEnd, 1, pcbStart);

    printf("Process %d created in memory [%d..%d]\n",
           pid, startIndex, pcbEnd);
}

/* 
 * Writes each source line into memory, naming each slot “instruction”
 * Returns number of lines written.
 */
int loadProgram(const char* filename, int memIdx) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error: cannot open %s\n", filename);
        return 0;
    }
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        writeMemory(memIdx + count, "instruction", line);
        count++;
    }
    fclose(f);
    return count;
}

/* 
 * Fill 5 PCB fields at pcbStartIndex:
 *   [0] processID, [1] state, [2] priority,
 *   [3] programCounter, [4] memoryBounds
 */
void initializePCB(int pid, int memLower, int memUpper, int priority, int pcbStartIndex)
{
    char *s;

    s = intToStr(pid);
    writeMemory(pcbStartIndex + 0, "processID", s);
    free(s);

    writeMemory(pcbStartIndex + 1, "state", "NEW");

    s = intToStr(priority);
    writeMemory(pcbStartIndex + 2, "priority", s);
    free(s);

    s = intToStr(memLower);
    writeMemory(pcbStartIndex + 3, "programCounter", s);
    free(s);

    char bounds[32];
    snprintf(bounds, sizeof(bounds), "%d-%d", memLower, memUpper);
    writeMemory(pcbStartIndex + 4, "memoryBounds", bounds);
}

void parseInstruction(char* instructionLine, int processId) {
    // el hyhandle instrution should do it .
}
