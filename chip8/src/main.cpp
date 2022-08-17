#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"
#include "chip8.h"

const int WIDTH = 400, HEIGHT = 800;

int main(int argc, char *argv[])
{
    Chip8 chip8;
    Renderer renderer;
    renderer.initializePlatform("Chips8", WIDTH, HEIGHT, chip8.CHIP8_WIDTH, chip8.CHIP8_HEIGHT);

    int pitch = sizeof(chip8.pixelBuffer[0]) * chip8.CHIP8_WIDTH;

    for (int i = 0; i < 1000; i++) {
        chip8.pixelBufferTestCode(chip8.pixelBuffer, i);
        renderer.update(chip8.pixelBuffer, pitch);
        SDL_Delay(25);
    }
    
    renderer.destoryChip8Screen();
    return 0;
}

/*
SDL_Window *Window = nullptr;
SDL_Renderer *Renderer;

int Init()
{
    int Success = 1;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL! SDL_GetError: %s\n", SDL_GetError());
        Success = 0;
    }
    else
    {
        Window = SDL_CreateWindow("SDL Test",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH,
                                  HEIGHT,
                                  0);    
        if(!Window)
        {
            SDL_Log("Failed to create window! SDL_GetError: %s\n", SDL_GetError());
            Success = 0;
        }
        else
        {
            Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(!Renderer)
            {
                SDL_Log("Failed to create renderer!\n");
                Success = 0;
            }
            else
            {   
                SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);
				
				int flags = IMG_INIT_PNG;
				int initted = IMG_Init(flags);
				if((initted&flags) != flags)
                {
					SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
					SDL_Log("IMG_Init: %s\n", IMG_GetError());
					Success = 0;
				}
            }
        }
    }
    
    return Success;
}

int main(int argc, char *argv[])
{
    if(!Init())
    {
        SDL_Log("Failed to initalize!\n");
    }
    else
    {
        int Running = 1;
        SDL_Event e;
        
        while(Running)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    Running = 0;
                }
            }
            
            SDL_SetRenderDrawColor(Renderer, 0xff, 0, 0, 0xff);
            SDL_RenderClear(Renderer);
            
            SDL_RenderPresent(Renderer);
        }
    }
    
    // Shutdown
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
	Renderer = NULL;
    Window =  NULL;
    
    IMG_Quit();
    SDL_Quit();
    return 0;
}
*/