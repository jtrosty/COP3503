#include "FileLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unordered_map< string, FileLoader::TextureData& > FileLoader::textures;

void FileLoader::loadAllTextures() {
    string listFileNames[] = { "mine",       "tile_hidden", "tile_revealed", 
                               "number_1",   "number_2",    "number_3", 
                               "number_4",   "number_5",    "number_6", 
                               "number_7",   "number_8",    "flag", 
                               "face_happy", "face_win",    "face_lose", 
                               "digits",     "debug",       "test_1", 
                               "test_2",     "test_3" };
    int size = 20;

    for (int i = 0; i < size; i++) {
        FileLoader::textures.emplace(listFileNames[i], getTextureString(listFileNames[i]));
    }
}

FileLoader::TextureData& FileLoader::getTextureBMP(string name) {
    return FileLoader::textures.at(name);
}

const unordered_map< string, FileLoader::TextureData& > getTextureMap() {
    return FileLoader::textures;
}

FileLoader::TextureData& FileLoader::getTextureChar(char* name) {
    return loadTextureData32Bit(readEntireFile(name));
}

FileLoader::TextureData& FileLoader::getTextureString(string name) {
    TextureData* result;
    string fileLocation = "../images/";
    string fileType = ".png";
    name = (fileLocation + name + fileType);
    int sizeString = name.size();
    char* pathChar = new char[sizeString + 1];

    // Copy String to Char
    for (int i = 0; i < sizeString; i++) {
        pathChar[i] = name.at(i);
    }
    pathChar[sizeString + 1] = '\0';
    
    result = &loadTextureData32Bit(readEntireFile(pathChar)); 
    delete[] pathChar;

    return *result;
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
    unsigned char temp0;
    unsigned char temp1;
    unsigned char temp2;
    unsigned char temp3;
    UINT32* destPixel;
    result->pixelData = stbi_load_from_memory((stbi_uc*)data.data, data.size, &result->width, &result->height, &result->n, 4);
    result->bitMapInfo.bmiHeader.biSize = sizeof(result->bitMapInfo.bmiHeader);
    result->bitMapInfo.bmiHeader.biWidth = result->width;
    result->bitMapInfo.bmiHeader.biHeight = -result->height;
    result->bitMapInfo.bmiHeader.biPlanes = 1;
    result->bitMapInfo.bmiHeader.biBitCount = 32;
    result->bitMapInfo.bmiHeader.biCompression = BI_RGB;
    result->bitMapInfo.bmiHeader.biSizeImage = 0;
    result->bitMapInfo.bmiHeader.biXPelsPerMeter = 0;
    int test = 0;


/*
    for (int i = 0; i < data.size; i = i + 4) {
        // NEED THESE LINES
        temp0 = result->pixelData[i];
        temp1 = result->pixelData[i + 1];
        temp2 = result->pixelData[i + 2];
        temp3 = result->pixelData[i + 3];
        
        // THIS HAS SHOWN TO BE CORRECT
        result->pixelData[i] = temp2;
        result->pixelData[i + 1] = temp1;
        result->pixelData[i + 2] = temp0;
        result->pixelData[i + 3] = temp3;

        // NOT USED
        result->pixelData[i] = result->pixelData[i] & 0x00000000;
        result->pixelData[i] = ((result->pixelData[i]) | ((temp >> 24) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp >> 8) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp >> 16) & 0x000000ff));

        *destPixel = ((*destPixel << 8) | ((temp) & 0x000000ff));
        *destPixel = ((*destPixel << 8) | ((temp >> 8) & 0x000000ff));
        *destPixel = ((*destPixel << 8) | ((temp >> 16) & 0x000000ff));
        *destPixel++;
       if (test == 100) break;
    }
 */

    return *result;
}