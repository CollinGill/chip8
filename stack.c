#include "include/stack.h"

Frame* createFrame(uint16_t data)
{
    Frame* newFrame = malloc(sizeof(Frame*));
    newFrame->address = 0x0000;
    newFrame->next = NULL;
    return newFrame;
}

Stack* initializeStack()
{
    Stack* newStack = malloc(sizeof(Stack*));
    newStack->head = NULL;
    newStack->size = 0;
    return newStack;
}

void push(Stack* stack, uint16_t address)
{
    Frame* newFrame = createFrame(address);
    newFrame->next = stack->head;
    stack->head = newFrame;
    stack->size++;
}

uint16_t pop(Stack* stack)
{
    uint16_t address = stack->head->address;
    Frame* obsolete = stack->head;
    stack->head = stack->head->next;
    free(obsolete);
    stack->size--;
    return address;
}