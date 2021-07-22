#pragma once
#include <string>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;

using std::string;
using std::ifstream;

class FileLoading {

	static void loadConfig(string fileName);

public:
	enum fileTypeToLoad {config, board};
	struct ConfigData {
		int column;
		int rows;
		int numOfMines;
	};
	static ConfigData configData;
	static void loadFileHelper(string fileName, fileTypeToLoad type);
};
