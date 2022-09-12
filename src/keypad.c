#include "./include/keypad.h"

void keyDown(SDL_Event event, CHIP8 *chip8)
{
    SDL_KeyCode pressedKey = event.key.keysym.sym; 

    switch (pressedKey)
    {
        case SDLK_ESCAPE:
            exit(0);

        case SDLK_1:
            chip8->keypad[0x1] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x1;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_2:
            chip8->keypad[0x2] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x2;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_3:
            chip8->keypad[0x3] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x3;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_4:
            chip8->keypad[0xC] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xC;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_q:
            chip8->keypad[0x4] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x4;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_w:
            chip8->keypad[0x5] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x5;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_e:
            chip8->keypad[0x6] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x6;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_r:
            chip8->keypad[0xD] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xD;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_a:
            chip8->keypad[0x7] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x7;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_s:
            chip8->keypad[0x8] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x8;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_d:
            chip8->keypad[0x9] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x9;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_f:
            chip8->keypad[0xE] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xE;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_z:
            chip8->keypad[0xA] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xA;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_x:
            chip8->keypad[0x0] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0x0;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_c:
            chip8->keypad[0xB] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xB;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        case SDLK_v:
            chip8->keypad[0xF] = true;
            if (chip8->waitForKeyPress) {
                chip8->V[chip8->keyReg] = 0xF;
                chip8->waitForKeyPress = false;
                chip8->PC += 2;
            }
            break;

        default:
            break;
    };
}

void keyUp(SDL_Event event, CHIP8 *chip8)
{
    SDL_KeyCode pressedKey = event.key.keysym.sym; 

    switch (pressedKey)
    {
        case SDLK_1:
            chip8->keypad[0x1] = false;
            break;

        case SDLK_2:
            chip8->keypad[0x2] = false;
            break;

        case SDLK_3:
            chip8->keypad[0x3] = false;
            break;

        case SDLK_4:
            chip8->keypad[0xC] = false;
            break;

        case SDLK_q:
            chip8->keypad[0x4] = false;
            break;

        case SDLK_w:
            chip8->keypad[0x5] = false;
            break;

        case SDLK_e:
            chip8->keypad[0x6] = false;
            break;

        case SDLK_r:
            chip8->keypad[0xD] = false;
            break;

        case SDLK_a:
            chip8->keypad[0x7] = false;
            break;

        case SDLK_s:
            chip8->keypad[0x8] = false;
            break;

        case SDLK_d:
            chip8->keypad[0x9] = false;
            break;

        case SDLK_f:
            chip8->keypad[0xE] = false;
            break;

        case SDLK_z:
            chip8->keypad[0xA] = false;
            break;

        case SDLK_x:
            chip8->keypad[0x0] = false;
            break;

        case SDLK_c:
            chip8->keypad[0xB] = false;
            break;

        case SDLK_v:
            chip8->keypad[0xF] = false;
            break;

        default:
            break;
    };

}