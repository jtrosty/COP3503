#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Platform.h"
#include "chip8.h"

int main(int argc, char *argv[])
{
    //Chip8 chip8("..\\ROM\\IBM_Logo.ch8");
    Chip8 chip8("..\\ROM\\test_opcode.ch8");
    //Chip8 chip8("..\\ROM\\c8_test.c8");
    Platform platform;
    int scale = 10;
    int width = chip8.CHIP8_WIDTH * scale;
    int heigth = chip8.CHIP8_HEIGHT * scale;
    platform.initializePlatform("Chips8", width, heigth, chip8.CHIP8_WIDTH, chip8.CHIP8_HEIGHT);

    int pitch = sizeof(chip8.pixelBuffer[0]) * chip8.CHIP8_WIDTH;

    bool run = true;
    int i = 0;
    while(run) {
        run = !platform.processInput(chip8.keypad);
        //chip8.pixelBufferTestCode(chip8.pixelBuffer, i++);
        chip8.emulateCycle();
        if (chip8.updateScreen) {
            platform.update(chip8.pixelBuffer, pitch);
            chip8.updateScreen = false;
        }
    }
    
    platform.destoryChip8Screen();
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