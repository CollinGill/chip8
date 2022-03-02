#ifndef CPU_H
#define CPU_H

#include "./stack.h"

#define DISPLAY_WIDTH   64
#define DISPLAY_HEIGHT  32  

typedef struct CHIP8
{
    uint8_t memArr[4096];
    uint8_t displayArr[DISPLAY_HEIGHT * DISPLAY_WIDTH];

    uint16_t PC;
    uint16_t I;

    uint8_t DT;
    uint8_t ST;

    struct Stack* chipStack;

    uint8_t V[0x10];
} CHIP8;

void initializeCHIP8(CHIP8* chip8);

void loadROM(CHIP8* chip8, char* fileLocation);

void printStatus(CHIP8* chip8);

void printDisplayBuff(CHIP8* chip8);

void regDump(CHIP8* chip8);

#endif
