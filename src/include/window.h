#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "./cpu.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320

typedef struct Chip8Window
{
    SDL_Window* window;
    SDL_Surface* screen;
} Chip8Window;

void initializeScreenWindow(Chip8Window* chipWindow);
void initializeScreenSurface(Chip8Window* chipWindow);
void initializeWindow(Chip8Window* chipWindow);

#endif