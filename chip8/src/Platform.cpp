#include "Platform.h"

void Platform::initializePlatform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
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

void Platform::update(void const* pixelBuffer, int pitch) { 

    // Get new texture 
    SDL_UpdateTexture(texture, NULL, pixelBuffer, pitch);
    // current renderer
    SDL_RenderClear(renderer);
    // Copies the new texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void Platform::destoryChip8Screen() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

bool Platform::processInput(uint8_t* keys) {
    SDL_Event event;
    bool quit = false;
    while (SDL_PollEvent( &event)) {

        switch (event.type) 
        {
        case SDL_QUIT: {
            quit = true;
        }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    quit = true;
                    break;
                }
                case SDLK_1: {
                    keys[0] = 1;
                    break;
                }
                case SDLK_2: {
                    keys[1] = 1;
                    break;
                }
                case SDLK_3: {
                    keys[2] = 1;
                    break;
                }
                case SDLK_4: {
                    keys[3] = 1;
                    break;
                }
                case SDLK_q: {
                    keys[4] = 1;
                    break;
                }
                case SDLK_w: {
                    keys[5] = 1;
                    break;
                }
                case SDLK_e: {
                    keys[6] = 1;
                    break;
                }
                case SDLK_r: {
                    keys[7] = 1;
                    break;
                }
                case SDLK_a: {
                    keys[8] = 1;
                    break;
                }
                case SDLK_s: {
                    keys[9] = 1;
                    break;
                }
                case SDLK_d: {
                    keys[10] = 1;
                    break;
                }
                case SDLK_f: {
                    keys[11] = 1;
                    break;
                }
                case SDLK_z: {
                    keys[12] = 1;
                    break;
                }
                case SDLK_x: {
                    keys[13] = 1;
                    break;
                }
                case SDLK_c: {
                    keys[14] = 1;
                    break;
                }
                case SDLK_v: {
                    keys[15] = 1;
                    break;
                }
            }
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_1: {
                    keys[0] = 0;
                    break;
                }
                case SDLK_2: {
                    keys[1] = 0;
                    break;
                }
                case SDLK_3: {
                    keys[2] = 0;
                    break;
                }
                case SDLK_4: {
                    keys[3] = 0;
                    break;
                }
                case SDLK_q: {
                    keys[4] = 0;
                    break;
                }
                case SDLK_w: {
                    keys[5] = 0;
                    break;
                }
                case SDLK_e: {
                    keys[6] = 0;
                    break;
                }
                case SDLK_r: {
                    keys[7] = 0;
                    break;
                }
                case SDLK_a: {
                    keys[8] = 0;
                    break;
                }
                case SDLK_s: {
                    keys[9] = 0;
                    break;
                }
                case SDLK_d: {
                    keys[10] = 0;
                    break;
                }
                case SDLK_f: {
                    keys[11] = 0;
                    break;
                }
                case SDLK_z: {
                    keys[12] = 0;
                    break;
                }
                case SDLK_x: {
                    keys[13] = 0;
                    break;
                }
                case SDLK_c: {
                    keys[14] = 0;
                    break;
                }
                case SDLK_v: {
                    keys[15] = 0;
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
    return quit;
}