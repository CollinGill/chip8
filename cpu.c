#include <stdio.h>
#include "include/cpu.h"

void initalizeCHIP8(CHIP8* chip8) {
    // Clear the memory
    for (int i = 0; i < 4096; i++)
        chip8->memArr[i] = 0;

    // Initialize the display to 0's
    for (int i = 0; i < (sizeof(chip8->displayArr) / sizeof(chip8->displayArr[0])); i++)
        chip8->displayArr[i] = 0x00;

    for (int i = 0; i < (sizeof(chip8->V) / sizeof(chip8->V[0])); i++)
        chip8->V[i] = 0x00;

    chip8->PC = 0x200;
    chip8->I = 0x00;
    chip8->DT = 0x00;
    chip8->ST = 0x00;

    uint8_t font[] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                      0x20, 0x60, 0x20, 0x20, 0x70, // 1
                      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
                      };

    chip8->chipStack = initializeStack();

    // Load the font into memory
    for (int i = 0; i < 80; i++)
        chip8->memArr[i] = font[i];
}

void printStatus(CHIP8 chip8)
{
    printf("Memory:\n\n");
    for (int i = 0; i < (sizeof(chip8.memArr) / sizeof(chip8.memArr[0])); i++)
    {
        if (chip8.memArr[i] != 0)
            printf("%d: %d\n", i, chip8.memArr[i]);
    }
}
