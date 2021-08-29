#pragma once

#include <windows.h>
#include <unordered_map>
using std::unordered_map;
#include <string.h>
#include <iostream>
using std::string;
using std::endl;
using std::cout;

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
    static char* convertToChar;

    FileLoader::FileLoader(); 
    FileLoader::~FileLoader();
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
	string getTestBoardString();
	void deleteTestBoardString();

    private:
    // char* for file names to be used in strToChar this is to prevent leaks

    // Helper functions for loading textures
	void loadFileHelper(string fileName, fileTypeToLoad type);
    static FileReadInData readEntireFile(char* path);
    static TextureData& loadTextureData32Bit(FileReadInData& data);

    // Helper fucntion to load in board
	void loadConfig(string fileName);
	//void loadBoard(string fileName);
    static char* stringToChar(string str);
};