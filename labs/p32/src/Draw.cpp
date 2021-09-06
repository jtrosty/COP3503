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

    for (int y = y0; y < y1; y++) {
        UINT32* destPixel = buffer.pixels + x0 + (y * buffer.width);
        for (int x = x0; x < x1; x++) {
            // TODO: Fix file loader so this is all I need to display
            //*destPixel++ = *srcPixel++;

            // TODO (Jon): this is done because the file loader because it loads 
            // textures with the pixels a little out of order, see FileLoader for
            // more. 
            *destPixel = ((*destPixel) | ((*srcPixel >> 24) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 8) & 0x000000ff));
            *destPixel = ((*destPixel << 8) | ((*srcPixel >> 16) & 0x000000ff));
            *srcPixel++;
            *destPixel++;
        }
    }
}

void Draw::drawTextureSubRectangle(int destX, int destY, Rect subTexture, 
                                    FileLoader::TextureData& texture, RenderBuffer& buffer) {
    //subTexture.x0 = clamp(0, subTexture.x0, buffer.width);
    //subTexture.x1 = clamp(0, subTexture.x1, buffer.width);
    //subTexture.y0 = clamp(0, subTexture.y0, buffer.height);
    //subTexture.y1 = clamp(0, subTexture.y1, buffer.height);
    //Top Left of Texture on buffer, ensure it is in bounds
    destX = clamp(0, destX, buffer.width);
    destY = clamp(0, destY, buffer.height);
    //Bottom Rigth of Texture on, ensure it is in bounds
    int destX1 = clamp(0, destX + subTexture.width, buffer.width);
    int destY1 = clamp(0, destY + subTexture.heigth, buffer.height);

    int start = 0;
    UINT32* srcPixel;// = (UINT32*)texture.pixelData[start];
    UINT32* destPixel;

    for (int y = destY; y < destY1; y++) {
        start = ((y - destY) * texture.width) + subTexture.x0;
        destPixel = buffer.pixels + destX + (y * buffer.width);
        srcPixel = (UINT32*)texture.pixelData + start;
        for (int x = destX; x < destX1; x++) {
            // TODO: Fix file loader so this is all I need to display
            //*destPixel++ = *srcPixel++;

            // TODO (Jon): this is done because the file loader because it loads 
            // textures with the pixels a little out of order, see FileLoader for
            // more. 
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