#pragma once
#include <Windows.h>
#include "utils.h"
#include "FileLoader.h"
#include <unordered_map>
using std::unordered_map;
#include <string.h>
using std::string;

class Draw {
    public:
    Draw();

    void drawRectangle(int x0, int y0, int x1, int y1, UINT32 color, RenderBuffer& buffer);
    int clamp(int min, int value, int max);
    void drawTexture(int x0, int y0, FileLoader::TextureData& texture, RenderBuffer& buffer);
    
    static unordered_map< string, FileLoader::TextureData > textures;


    private:

};