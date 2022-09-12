#ifndef RUN_H
#define RUN_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./keypad.h"
#include "./window.h"

void run(char* rom);
bool instructions(uint16_t opcode, CHIP8* chip8);

#endif 