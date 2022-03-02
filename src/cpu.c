#include <stdio.h>
#include "include/cpu.h"

void initializeCHIP8(CHIP8* chip8) {
    // Clear the memory
    for (int i = 0; i < (sizeof(chip8->memArr) / sizeof(chip8->memArr[0])); i++)
        chip8->memArr[i] = 0;

    // Initialize the display to 0's
    for (int i = 0; i < (sizeof(chip8->displayArr) / sizeof(chip8->displayArr[0])); i++)
        chip8->displayArr[i] = 0;

    /*
     * The display is 64x32
     * Therefore, for a given position (x,y), its position in the array would be 64x+y 
     */

    for (int i = 0; i < (sizeof(chip8->V) / sizeof(chip8->V[0])); i++)
        chip8->V[i] = 0x00;

    chip8->PC = 0x0200;
    chip8->I = 0x0000;
    chip8->DT = 0x0000;
    chip8->ST = 0x0000;

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

void loadROM(CHIP8* chip8, char* file)
{
    // Reads the ROM
    FILE* rom = fopen(file, "rb");

    // Checks if the ROM is empty
    if (rom == NULL) {
        printf("\nERROR: ROM is empty.\n");
        exit(1);
    }

    // Creating the buffer then initializing it to 0's
    uint8_t buffer[0x0E00];
    for (int i = 0; i < (sizeof(buffer) / sizeof(buffer[0])); i++)
        buffer[i] = 0;

    fread(buffer, sizeof(buffer), 1, rom);

    for (int i = 0; i < (sizeof(buffer) / sizeof(buffer[0])); i++) {
        chip8->memArr[chip8->PC] = buffer[i] ;//<< 8 | buffer[i + 1];
        chip8->PC++;
    }

    fclose(rom);

    chip8->PC = 0x0200;
}

void printStatus(CHIP8* chip8)
{
    for (int i = 0; i < (sizeof(chip8->memArr) / sizeof(chip8->memArr[0])); i++) {
        //if (chip8->memArr[i] != 0)
            printf("%03X | %02X\n", i, chip8->memArr[i]);
    }
}

void printDisplayBuff(CHIP8* chip8)
{
    for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) {
        if (i % 64 == 0 && i != 0)
            printf("\n");
        if (chip8->displayArr[i]== 1)
            printf("*");
        else
            printf(" ");
    }

    printf("\n");
}

void regDump(CHIP8* chip8)
{
    printf("DEBUG\n");
    for (int i = 0; i < 0x10; i++)
        printf("\tV[%X]: %02X\n", i, chip8->V[i]);
    printf("\t   I: %03X\n", chip8->I);
}