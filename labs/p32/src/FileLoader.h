#pragma once

#include <windows.h>
#include <unordered_map>
using std::unordered_map;
#include <string.h>
using std::string;

class FileLoader {

    public:
	struct FileReadInData {
		LPVOID data;
		DWORD size;
	};

    struct TextureData {
        int width;
        int height;
        int n;
        unsigned char* pixelData;
        BITMAPINFO bitMapInfo; 
    };
    static unordered_map< string, TextureData& > textures;

    static TextureData& getTextureChar(char* name);
    static TextureData& getTextureString(string name);
    static void loadAllTextures();
    TextureData& getTextureBMP(string name);

    static const unordered_map< string, TextureData& > getTextureMap();

    private:
    static FileReadInData readEntireFile(char* path);
    static TextureData& loadTextureData32Bit(FileReadInData data);
};