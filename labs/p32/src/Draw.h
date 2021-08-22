#pragma once
#include <Windows.h>
#include "utils.h"
#include "FileLoader.h"

class Draw {
    public:
    void drawRectangle(int x0, int y0, int x1, int y1, UINT32 color, RenderBuffer& buffer);
    int clamp(int min, int value, int max);
    void drawTexture(int x0, int y0, FileLoader::TextureData& texture, RenderBuffer& buffer);


    private:

};