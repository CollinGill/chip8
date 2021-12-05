#include "./include/window.h"

void initializeScreenWindow(Chip8Window* chipWindow)
{
    chipWindow->window = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    chipWindow->window = SDL_CreateWindow("Chip8 Emulator",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    
    if (!chipWindow->window) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
}

void initializeScreenSurface(Chip8Window* chipWindow)
{
    chipWindow->screen = NULL;
    chipWindow->screen = SDL_GetWindowSurface(chipWindow->window);
    SDL_FillRect(chipWindow->screen,
                 NULL,
                 SDL_MapRGB(chipWindow->screen->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(chipWindow->window);
}

void initializeWindow(Chip8Window* chipWindow)
{
    initializeScreenWindow(chipWindow);
    initializeScreenSurface(chipWindow);
}