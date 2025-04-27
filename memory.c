
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "memory.h"

//char* memory[MEMORY_SIZE];

void initMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = NULL;
    }
}

int allocateMemory(int size) {
    int count = 0;
    int start = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == NULL) {
            if (count == 0) start = i;
            count++;
            if (count == size) {
                return start;
            }
        } else {
            count = 0;
            start = -1;
        }
    }
    return -1; // Not enough contiguous memory
}

void freeMemory(int start, int size) {
    for (int i = start; i < start + size && i < MEMORY_SIZE; i++) {
        if (memory[i] != NULL) {
            free(memory[i]);
            memory[i] = NULL;
        }
    }
}

void writeToMemory(int index, const char* data) { // edit code
    if (index >= 0 && index < MEMORY_SIZE) {
        if (memory[index] != NULL) {
            free(memory[index]);
        }
        memory[index] = (char*)malloc(strlen(data) + 1);
        if (memory[index] != NULL) {
            strcpy(memory[index], data);
        }
    }
}

char* readFromMemory(int index) {
    if (index >= 0 && index < MEMORY_SIZE && memory[index] != NULL) {
        return memory[index];
    }
    return NULL;
}

void printMemory() {
    printf("\n===== Memory State =====\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] != NULL) {
            printf("[%02d]: %s\n", i, memory[i]);
        } else {
            printf("[%02d]: (empty)\n", i);
        }
    }
    printf("=========================\n\n");
}
