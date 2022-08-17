#include <SDL.h>
#include <iostream>

class Renderer {

    public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    // TODO: delte all these? 
    SDL_Rect* chip8Rect = nullptr;
    SDL_Rect* windowRect = nullptr;
    SDL_Surface* chip8Surface = nullptr;
    SDL_Surface* windowSurface = nullptr;
    SDL_Palette* windowPalette = nullptr;

    void initializePlatform(const char* title, int windowsWidth, int windowHeight);

    void update(void const* pixelBuffer, int pitch);

    void destoryChip8Screen();
};