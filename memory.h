#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 60

typedef struct {
    char *name;
    char *value;
} MemoryWord;

void initMemory(void);
int  allocateMemory(int size);
void freeMemory(int start, int size);
void writeMemory(int index, const char *name, const char *value);
char *readMemoryValue(int index);
void printMemory(void);

#endif /* MEMORY_H */
