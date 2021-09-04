#ifndef CPU_H
#define CPU_H

#include "./stack.h"

typedef struct CHIP8
{
    uint8_t memArr[4096];
    uint8_t displayArr[64*32];

    uint8_t PC;
    uint16_t I;

    uint8_t DT;
    uint8_t ST;

    struct Stack* chipStack;

    uint8_t V[0x10];
} CHIP8;

void initalizeCHIP8(CHIP8* chip8);

void printStatus(CHIP8 chip8);

#endif
