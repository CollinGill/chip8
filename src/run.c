#include "./include/run.h"

void run(char* rom)
{
    CHIP8 chip8;
    initializeCHIP8(&chip8);
    loadROM(&chip8, rom);

    Chip8Window chipWindow;
    initializeWindow(&chipWindow);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_Log("QUIT");
                    running = false;
                    break;
            }
        }
    }
    SDL_DestroyWindow((&chipWindow)->window);
    SDL_Quit();
}