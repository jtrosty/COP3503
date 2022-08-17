#include "Renderer.h"

void Renderer::initializePlatform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
    }
    else {
        window = SDL_CreateWindow(
                                title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                windowWidth, 
                                windowHeight,
                                SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(
                                    renderer, 
                                    SDL_PIXELFORMAT_ARGB8888, 
                                    SDL_TEXTUREACCESS_STREAMING,
                                    textureWidth,
                                    textureHeight);


        if (window == NULL) {
            std::cout << "Window creation error: " << SDL_GetError() << std::endl;
        }
        if (renderer == NULL) {
            std::cout << "Renderer creation error: " << SDL_GetError() << std::endl;
        }
        if (texture == NULL) {
            std::cout << "Texture creation error: " << SDL_GetError() << std::endl;
        }
    }
}

void Renderer::update(void const* pixelBuffer, int pitch) { 

    // Get new texture 
    SDL_UpdateTexture(texture, NULL, pixelBuffer, pitch);
    // current renderer
    SDL_RenderClear(renderer);
    // Copies the new texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void Renderer::destoryChip8Screen() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}