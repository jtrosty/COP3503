#include <SDL.h>
#include <iostream>

class Renderer {
    const int CHIP8_HEIGHT = 64;
    const int CHIP8_WIDTH = 32;
    const int WINDOW_HEIGHT = 640;
    const int WINDOW_WIDTH = 320;

    public:
    //TODO: Delete

    int testColor = 0xFFFFFF;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* windowTexture = nullptr;
    SDL_Rect* chip8Rect = nullptr;
    SDL_Rect* windowRect = nullptr;
    SDL_Surface* chip8Surface = nullptr;
    SDL_Surface* windowSurface = nullptr;
    SDL_Palette* windowPalette = nullptr;

    uint32_t* chip8Pixels = new uint32_t[CHIP8_HEIGHT * CHIP8_WIDTH];
    uint32_t* windowPixels = new uint32_t[WINDOW_HEIGHT * WINDOW_WIDTH];

    SDL_PixelFormat* pixelFormat;


    void initializeChip8Screen();

    void updateChip8Screen();

    void destoryChip8Screen();
};