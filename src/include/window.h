#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "./cpu.h"

#define WINDOW_WIDTH 1280 
#define WINDOW_HEIGHT 640 

typedef struct Chip8Window
{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Chip8Window;

void initializeWindow(Chip8Window* chipWindow, CHIP8* chip8);
void initializeScreenWindow(Chip8Window* chipWindow);
void initializeScreenSurface(Chip8Window* chipWindow);
void initializeTexture(Chip8Window* chipWindow);
void initializeRenderer(Chip8Window* chipWindow);
void drawScreen(Chip8Window* chipWindow, CHIP8* chip8);

#endif