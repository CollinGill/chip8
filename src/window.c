#include "./include/window.h"

void initializeScreenWindow(Chip8Window* chipWindow)
{
    chipWindow->window = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    chipWindow->window = SDL_CreateWindow("Chip8 Emulator",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
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
    //SDL_FillRect(chipWindow->screen,
    //             NULL,
    //             SDL_MapRGB(chipWindow->screen->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(chipWindow->window);
}

void initializeRenderer(Chip8Window* chipWindow)
{
    chipWindow->renderer = SDL_CreateRenderer(chipWindow->window, -1, SDL_RENDERER_ACCELERATED);
}

void initializeTexture(Chip8Window* chipWindow)
{
    chipWindow->texture = SDL_CreateTexture(chipWindow->renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

void initializeWindow(Chip8Window* chipWindow, CHIP8* chip8)
{
    initializeScreenWindow(chipWindow);
    initializeRenderer(chipWindow);
    initializeTexture(chipWindow);
    initializeScreenSurface(chipWindow);

    SDL_SetRenderDrawColor(chipWindow->renderer, 0, 0, 0, 0);
    SDL_RenderClear(chipWindow->renderer);
    SDL_RenderPresent(chipWindow->renderer);
}

void drawScreen(Chip8Window* chipWindow, CHIP8* chip8)
{
    SDL_UpdateTexture(chipWindow->texture, NULL, chip8->displayArr, DISPLAY_WIDTH * sizeof(uint8_t));
    SDL_RenderClear(chipWindow->renderer);
    SDL_RenderCopy(chipWindow->renderer, chipWindow->texture, NULL, NULL);
    SDL_RenderPresent(chipWindow->renderer);
}