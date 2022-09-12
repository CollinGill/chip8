#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdlib.h>

typedef struct Frame
{
    uint16_t address;
    struct Frame* next;
} Frame;


typedef struct Stack
{
    struct Frame* head;
    int size;
} Stack;

Frame* createFrame(uint16_t data);

Stack* initializeStack();

void push(Stack* stack, uint16_t address);

uint16_t pop(Stack* stack);

#endif