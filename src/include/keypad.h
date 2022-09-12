#ifndef KEYPAD_H
#define KEYPAD_H

#include <SDL2/SDL.h>
#include "./cpu.h"

/*  1 2 3 C
 *  4 5 6 D
 *  7 8 9 E
 *  A 0 B F
 */

// Possibly could go in run.h/run.c but the file is getting a little cluttered
void keyDown(SDL_Event event, CHIP8 *chip8);
void keyUp(SDL_Event event, CHIP8 *chip8);

#endif