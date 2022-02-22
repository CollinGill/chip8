#include "./include/run.h"

void run(char* rom)
{
    CHIP8 chip8;
    initializeCHIP8(&chip8);
    loadROM(&chip8, rom);

    Chip8Window chipWindow;
    initializeWindow(&chipWindow);

    int count = 1;
    bool running = true;
    while (running) {
        SDL_Event event;


        uint16_t opcode = (chip8.memArr[chip8.PC] << 8) | chip8.memArr[chip8.PC + 1];
        printf("%04X |\t %04X\n", chip8.PC, opcode);
        running = instructions(opcode, &chip8); // uncomment the `running =` part in order to test if opcodes are valid
        
        // TODO: Implement the delay and sound timers at 60Hz
        if (chip8.DT != 0x0000) {
            chip8.DT--;
        }


        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_Log("QUIT");
                    running = false;
                    break;
            }
        }

        count++;
    }
    SDL_DestroyWindow((&chipWindow)->window);
    SDL_Quit();
}


bool instructions(uint16_t opcode, CHIP8* chip8)
{
    uint16_t firstDigit = opcode & 0x000F;
    uint16_t secondDigit = (opcode & 0x00F0) >> 4;
    uint16_t thirdDigit = (opcode & 0x0F00) >> 8;
    uint16_t fourthDigit = (opcode & 0xF000) >> 12;

    // printf("%x\n%x\n%x\n%x\n", firstDigit, secondDigit, thirdDigit, fourthDigit); // For debugging opcodes

    switch (fourthDigit)
    {

    case 0x0:
    {
        switch (secondDigit)
        {
        case 0xE:
        {
            switch (firstDigit)
            {
            case 0x0:
            {
                // 0x00E0: Clear display
                for (int i = 0; i < (sizeof(chip8->displayArr) / sizeof(chip8->displayArr[0])); i++)
                    chip8->displayArr[i] = 0x00;
                chip8->PC += 2;
                break;
            }
            case 0xE:
            {
                // 0x00EE: Returns from subroutine
                uint16_t address = pop(chip8->chipStack);
                chip8->PC = address;
                break;
            }
            default:
            {
                printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
                return false;
                break;
            }
        }
            break;
        }
        default:
        {
            printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
            return false;
            break;
        }
        }
        break;
    }

    case 0x1:
    {
        // 0x1NNN: Jumps to address NNN
        uint16_t address = opcode & 0x0FFF;
        chip8->PC = address;
        break;
    }

    case 0x2:
    {
        // 0x2NNN: Calls subroutine at 0x0NNN
        uint16_t address = opcode & 0x0FFF;
        push(chip8->chipStack, chip8->PC);
        chip8->PC = address;
        break;
    }

    case 0x3:
    {
        // 0x3XNN: if V[X] == NN, skip next instruction
        uint8_t value = (opcode & 0x00FF) << 8;
        if (chip8->V[secondDigit] == value) {
            chip8->PC += 4;
        } else {
            chip8->PC += 2;
        }
        break;
    }

    case 0x4:
    {
        // 0x4XNN: if V[X] != NN, skip next instruction
        uint8_t value = (opcode & 0x00FF) << 8;
        if (chip8->V[secondDigit] != value) {
            chip8->PC += 4;
        } else {
            chip8->PC += 2;
        }
        break;
    }

    case 0x5:
    {
        switch (firstDigit)
        {
        case 0x0:
        {
            // 0x5XY0: if V[X] == V[Y], skip next instruction
            if (chip8->V[secondDigit] == chip8->V[thirdDigit]) {
                chip8->PC += 4;
            } else {
                chip8->PC += 2;
            }
            break;
        }
        default:
        {
            printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
            return false;
            break;
        }
        }
        break;
    }

    case 0x6:
    {
        // 0x6XNN: Set V[X] to NN
        uint8_t value = opcode & 0x00FF;
        chip8->V[thirdDigit] = value;
        chip8->PC += 2;
        break;
    }

    case 0x7:
    {
        // 0x7XNN: Adds NN to V[X]
        uint8_t value = opcode & 0x00FF;
        chip8->V[thirdDigit] += value;
        chip8->PC += 2;
        break;

    }

    case 0x8:
    {
        switch (firstDigit)
        {
        case 0x0:
        {
            // 0x8XY0: Sets V[X] to the value of V[Y]
            uint8_t value = chip8->V[secondDigit];
            chip8->V[thirdDigit] = value;
            chip8->PC += 2;
            break;
        }

        case 0x1:
        {
            // 0x8XY1: Sets V[X] to V[X] or V[Y]
            chip8->V[thirdDigit] |= chip8->V[secondDigit];
            chip8->PC += 2;
            break;
        }

        case 0x2:
        {
            // 0x8XY2: Sets V[X] to V[X] and V[Y]
            chip8->V[thirdDigit] &= chip8->V[secondDigit];
            chip8->PC += 2;
            break;
        }
        
        case 0x3:
        {
            // 0x8XY3: Sets V[X] to V[X] xor V[Y]
            chip8->V[thirdDigit] ^= chip8->V[secondDigit];
            chip8->PC += 2;
            break;
        }
        
        case 0x4:
        {
            // 0x8XY4: Sets V[X] to V[X] + V[Y], sets V[F] to 1 if carry
            uint16_t sum = chip8->V[thirdDigit] + chip8->V[secondDigit];

            chip8->V[thirdDigit] = (uint8_t)(sum & 0x00FF);
            if ((sum & 0xFF00) > 0) {
                chip8->V[0xF] = 1;
            } else {
                chip8->V[0xF] = 0;
            }
            chip8->PC += 2;
            break;
        }

        case 0x5:
        {
            // 0x8XY5: Sets V[X] to V[X] - V[Y], sets V[F] to 1 if there's a borrow 
            uint16_t diff = chip8->V[thirdDigit] - chip8->V[secondDigit];

            chip8->V[thirdDigit] = (uint8_t)(diff & 0x00FF);
            if (chip8->V[thirdDigit] > chip8->V[secondDigit]) {
                chip8->V[0xF] = 1;
            } else {
                chip8->V[0xF] = 0;
            }
            chip8->PC += 2;
            break;
        }

        case 0x6:
        { 
            // 0x8XY6: Stores the least significant bit to V[F] then right shifts by 1
            chip8->V[0xF] = (uint8_t)firstDigit;
            chip8->V[thirdDigit] >>= 1;
            chip8->PC += 2;
            break;
        }

        case 0x7:
        {
            // 0x8XY7: Sets V[X] to V[Y] - V[X] and sets V[F]to 0 when there's a borrow
            uint16_t diff = chip8->V[secondDigit] - chip8->V[thirdDigit];

            chip8->V[thirdDigit] = (uint8_t)(diff & 0x00FF);
            if (chip8->V[thirdDigit] < chip8->V[secondDigit]) {
                chip8->V[0xF] = 1;
            } else {
                chip8->V[0xF] = 0;
            }
            chip8->PC += 2;
            break;
        }

        case 0xE:
        {
            // 0x8XYE: Stores the most significant bit to V[F] then left shifts by 1
            chip8->V[0xF] = (uint8_t)fourthDigit;
            chip8->V[thirdDigit] <<= 1;
            chip8->PC += 2;
            break;
        }

        default:
        {
            printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
            return false;
            break;
        }
        }

        break;
    }

    case 0x9:
    {
        switch (firstDigit)
        {
            case 0x0:
            {
                // 0x9XY0: Skips the next instruction if V[X] != V[Y]
                if (chip8->V[thirdDigit] != chip8->V[secondDigit]) {
                    chip8->PC += 4;
                } else {
                    chip8->PC += 2;
                }
                break;
            }
            default:
            {
                printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
                return false;
                break;
            }
        }
        break;
    }

    case 0xA:
    {
        // 0xANNN: Set I to NNN
        uint16_t address = opcode & 0x0FFF;
        chip8->I = address;
        chip8->PC += 2;
        break;
    }

    case 0xB:
    {
        // 0xBNNN: Jumps to the address NNN plus V[0]
        uint16_t address = opcode & 0x0FFF;
        chip8->PC = address + chip8->V[0];
        break;
    }

    case 0xC:
    {
        // 0xCXNN: Sets V[X] to teh result of a bitwise and on a random number [0,255]
        uint16_t randNum = 0x45; // Hardcoded for now
        uint16_t value = opcode & 0x00FF;
        chip8->V[secondDigit] = randNum & value;
        chip8->PC += 2;
        break;
    }

    case 0xD:
    {
        // 0xDXYN: Draw a sprite at (V[x],V[Y]) that has a width of 8 pixels and a height of N pixels
        // Each row of 8 pixels is read as bit-coded starting from memory location I (doesn't change after instruction)
        // V[F] is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, else 0

        uint8_t pos = 64 * chip8->V[thirdDigit] + chip8->V[secondDigit];

        chip8->PC += 2;
        break;
    }

    case 0xE:
    {
        switch ((secondDigit << 4) | firstDigit)
        {
            case 0x9E:
            {
                chip8->PC += 2;
                break;
            }
            case 0xA1:
            {
                chip8->PC += 2;
                break;
            }
            default:
            {
                printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
                return false;
                break;
            }
        }

        break;
    }

    case 0xF:
    {
        switch ((secondDigit << 4) | firstDigit)
        {
            case 0x07:
            {
                chip8->PC += 2;
                break;
            }
            case 0x0A:
            {
                chip8->PC += 2;
                break;
            }
            case 0x15:
            {
                chip8->PC += 2;
                break;
            }
            case 0x18:
            {
                chip8->PC += 2;
                break;
            }
            case 0x1E:
            {
                chip8->PC += 2;
                break;
            }
            case 0x29:
            {
                chip8->PC += 2;
                break;
            }
            case 0x33:
            {
                chip8->PC += 2;
                break;
            }
            case 0x55:
            {
                chip8->PC += 2;
                break;
            }
            case 0x65:
            {
                chip8->PC += 2;
                break;
            }
            default:
            {
                printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
                return false;
                break;
            }
        }
        break;
    }
    
    default:
    {
        printf("\nERROR: Unrecognized OP-code|\t`%04x` at %04x\n", opcode, chip8->PC);
        return false;
        break;
    }
    }

    return true;
}