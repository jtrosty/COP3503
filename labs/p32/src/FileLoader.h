#pragma once

#include <windows.h>
#include <unordered_map>
using std::unordered_map;
#include <string.h>
using std::string;

class FileLoader {

    public:
    // Data types
	struct FileReadInData {
		LPVOID data;
		DWORD size;
	};

	struct ConfigData {
		int column;
		int rows;
		int numOfMines;
	};

    struct TextureData {
        int width;
        int height;
        int n;
        unsigned char* pixelData;
        BITMAPINFO bitMapInfo; 
    };

    // ENUM
	enum fileTypeToLoad {config, board};

    // ALL TEXTURES FOR THE GAME
    static unordered_map< string, TextureData& > textures;

    // Functionst in Support lof loading and getting textures
    static TextureData& getTextureChar(char* name);
    static TextureData& getTextureString(string name);
    static void loadAllTextures();
    TextureData& getTextureBMP(string name);

    static const unordered_map< string, TextureData& > getTextureMap();

    // Functiosn in support of configuring and test boards
	static ConfigData staticConfigData;
	ConfigData* configData;
	void loadFileHelper(string fileName, fileTypeToLoad type);
	string getTestBoardString();
	void deleteTestBoardString();

    private:
    // Helper functions for loading textures
    static FileReadInData readEntireFile(char* path);
    static TextureData& loadTextureData32Bit(FileReadInData data);

    // Helper fucntion to load in board
	void loadConfig(string fileName);
	void loadBoard(string fileName);
};