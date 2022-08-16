#include "Renderer.h"

void Renderer::initializeChip8Screen() {
    

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
    }
    else {
        window = SDL_CreateWindow("Chip 8 Screen", 
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, 
                                WINDOW_HEIGHT,
                                SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        windowTexture = SDL_CreateTexture(renderer, 
                                    SDL_PIXELFORMAT_ARGB8888, 
                                    SDL_TEXTUREACCESS_STREAMING,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT);

        chip8Pixels[0] = 0xFF44AA00; 
        chip8Rect = new SDL_Rect;
        windowRect = new SDL_Rect;
        chip8Rect = new SDL_Rect();
        chip8Rect->x = 0;
        chip8Rect->y = 0;
        chip8Rect->w = CHIP8_WIDTH;
        chip8Rect->h = CHIP8_HEIGHT;
        windowRect->x = 0;
        windowRect->y = 0;
        windowRect->w = WINDOW_WIDTH;
        windowRect->h = WINDOW_HEIGHT;
        chip8Surface = new SDL_Surface();
        chip8Surface->format = pixelFormat;
        chip8Surface->w = chip8Rect->w;
        chip8Surface->h = chip8Rect->h;
        chip8Surface->pitch = chip8Rect->w;
        chip8Surface->pixels = chip8Pixels;
        chip8Surface->clip_rect = *chip8Rect;
        windowSurface = new SDL_Surface;
        windowSurface->format = pixelFormat;
        windowSurface->format = pixelFormat;
        windowSurface->w = windowRect->w;
        windowSurface->h = windowRect->h;
        windowSurface->pitch = windowRect->w;
        windowSurface->pixels = windowPixels;
        windowSurface->clip_rect = *windowRect;


        if (window == NULL) {
            std::cout << "Window creation error: " << SDL_GetError() << std::endl;
        }
        if (renderer == NULL) {
            std::cout << "Renderer creation error: " << SDL_GetError() << std::endl;
        }
        else {
            windowSurface = SDL_GetWindowSurface(window);
            SDL_BlitSurface(windowSurface, NULL, windowSurface, NULL);

            //SDL_UpdateWindowSurface(window);
            SDL_Delay(1000);
        }
    }
}

void Renderer::updateChip8Screen() { 

        // TEST CODE DELETE
        
        for (int j = 0; j < 100; j++) {
            for (int i = 0; i < (32 * 64); i++) {
                chip8Pixels[i] = testColor; 
                testColor = testColor << 2;
            }
            // END TEST CODE
        if (SDL_BlitScaled(chip8Surface, chip8Rect, windowSurface, windowRect) < 0) {
            std::cout << "BlitScaled error creation error: " << SDL_GetError() << std::endl;
        }
            SDL_UpdateTexture(windowTexture, NULL, windowPixels, WINDOW_WIDTH);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, windowTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }

}

void Renderer::destoryChip8Screen() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(windowTexture);
    SDL_Quit();
}