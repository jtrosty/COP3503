#pragma once

#include <windows.h>


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

    static TextureData& getTexture(char* path);

    private:
    static FileReadInData readEntireFile(char* path);
    static TextureData& loadTextureData32Bit(FileReadInData data);


};