/* memory.c */
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static MemoryWord memory[MEMORY_SIZE];

void initMemory(void) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].name  = NULL;
        memory[i].value = NULL;
    }
}

int allocateMemory(int size) {
    int count = 0, start = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].name == NULL) {
            if (count == 0) start = i;
            if (++count == size) return start;
        } else {
            count = 0;
        }
    }
    return -1;
}

// by3ml kol haga fel memory null incase 3ayz ye restart
void freeMemory(int start, int size) {
    for (int i = start; i < start + size && i < MEMORY_SIZE; i++) {
        free(memory[i].name);
        free(memory[i].value);
        memory[i].name  = NULL;
        memory[i].value = NULL;
    }
}

void writeMemory(int index, const char *name, const char *value) {
    if (index < 0 || index >= MEMORY_SIZE) return;
    free(memory[index].name);
    free(memory[index].value);
    memory[index].name  = strdup(name);
    memory[index].value = strdup(value);
}

char *readMemoryValue(int index) {
    if (index < 0 || index >= MEMORY_SIZE) return NULL;
    return memory[index].value;
}

void printMemory(void) {
    printf("\n===== Memory State =====\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].name)
            printf("[%02d]: %s -> %s\n", i, memory[i].name, memory[i].value);
        else
            printf("[%02d]: (empty)\n", i);
    }
    printf("=========================\n\n");
}
