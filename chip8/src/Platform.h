#include <SDL.h>
#include <iostream>

class Platform {

    public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    void initializePlatform(const char* title, int windowsWidth, int windowHeight, int textureWidth, int textureHeight);

    void update(void const* pixelBuffer, int pitch);

    void destoryChip8Screen();

    bool processInput(uint8_t* keys);
};