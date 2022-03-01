#ifndef RUN_H
#define RUN_H

#include "./window.h"
#include "stdint.h"
#include "time.h"
#include "unistd.h"

void run(char* rom);
bool instructions(uint16_t opcode, CHIP8* chip8);

#endif 