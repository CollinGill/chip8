#include <stdio.h>
#include "include/cpu.h"

// ----------------------------------------------------------------------
//                          Design Specifications
// ----------------------------------------------------------------------
// Memory: direct access to up to 4kB of RAM - 4096 bytes
// Display: 64 x 32 pixels
// Program counter, points to current instruction
// 16-bit index register, I, which is used to point at location in memory
// A stack for 16-bit addresses, used to call subroutines/functions and return form then
// 8-bit sound timer, decrements at a rate of 60Hz
// 8-bit delay timer, beeping sound as long as it's not 0
// 16 8-bit general-purpose variable registers (0-F)

// CHIP-8 programs should be loaded into memory starting at address 0x200

int main(int argc, char* argv[])
{
    CHIP8 chip8;
    initializeCHIP8(&chip8);

    if (argc <= 1)
    {
        printf("ERROR: Must include rom.\n");
        exit(1);
    }
    else
    {
        loadROM(&chip8, argv[1]);
        printStatus(&chip8);
    }

    return 0;
}
