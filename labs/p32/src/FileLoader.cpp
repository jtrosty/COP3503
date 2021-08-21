#include "FileLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

FileLoader::TextureData& FileLoader::getTexture(char* path) {
    return loadTextureData32Bit(readEntireFile(path));
}

FileLoader::FileReadInData FileLoader::readEntireFile(char* path) {
    FileReadInData result = {0};

    DWORD fileSizeHigh = 0;
    DWORD bytesRead = 0;

    HANDLE fileHandle = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    result.size = GetFileSize(fileHandle, &fileSizeHigh);
    
    // Allocate memory for the file to be read
    result.data = VirtualAlloc( NULL, result.size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (ReadFile( fileHandle, result.data, result.size, &bytesRead, NULL) && result.size == bytesRead) {
        // Success, We read the file.
    }  
    else {
        // Fail!!!
    }

    return result;
}

FileLoader::TextureData& FileLoader::loadTextureData32Bit(FileReadInData data) {
    TextureData* result = new TextureData;
    result->pixelData = stbi_load_from_memory((stbi_uc*)data.data, data.size, &result->width, &result->height, &result->n, 4);
    result->bitMapInfo.bmiHeader.biSize = sizeof(result->bitMapInfo.bmiHeader);
    result->bitMapInfo.bmiHeader.biWidth = result->width;
    result->bitMapInfo.bmiHeader.biHeight = -result->height;
    result->bitMapInfo.bmiHeader.biPlanes = 1;
    result->bitMapInfo.bmiHeader.biBitCount = 32;
    result->bitMapInfo.bmiHeader.biCompression = BI_RGB;
    result->bitMapInfo.bmiHeader.biSizeImage = 0;
    result->bitMapInfo.bmiHeader.biXPelsPerMeter = 0;
    return *result;
}