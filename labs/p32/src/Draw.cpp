#include "Draw.h"

unordered_map< string, FileLoader::TextureData> textures;

Draw::Draw() {
}

void Draw::drawRectangle(int x0, int y0, int x1, int y1, UINT32 color, RenderBuffer& buffer) {
    x0 = clamp(0, x0, buffer.width);
    x1 = clamp(0, x1, buffer.width);
    y0 = clamp(0, y0, buffer.height);
    y1 = clamp(0, y1, buffer.height);

    for (int y = y0; y < y1; y++) {
        UINT32* pixel = buffer.pixels + x0 + (y * buffer.width);
        for (int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}

void Draw::drawTexture(int x0, int y0, FileLoader::TextureData& texture, RenderBuffer& buffer) {
    x0 = clamp(0, x0, buffer.width);
    int x1 = clamp(0, x0 + texture.width, buffer.width);
    y0 = clamp(0, y0, buffer.height);
    int y1 = clamp(0, y0 + texture.height, buffer.height);
    UINT32* srcPixel = (UINT32*)texture.pixelData;
    unsigned char fullByte = 255;
    unsigned char emptyByte = 0;

    for (int y = y0; y < y1; y++) {
        UINT32* destPixel = buffer.pixels + x0 + (y * buffer.width);
        for (int x = x0; x < x1; x++) {
            //*destPixel++ = *srcPixel++;
/*
            *destPixel = ((*destPixel << 8) | ((*srcPixel) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 8) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 16) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 24) & 0x000000ff));
            *srcPixel++;
            *destPixel++;
            */
            *destPixel = ((*destPixel) | ((*srcPixel >> 24) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 8) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 16) & 0x000000ff));
            *srcPixel++;
            *destPixel++;
        }
    }
}

int Draw::clamp(int min, int value, int max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}