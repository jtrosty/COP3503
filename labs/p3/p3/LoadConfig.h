#pragma once
#include <string>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;

using std::string;
using std::ifstream;

class FileLoading {
	void loadConfig(string fileName);

public:
	struct ConfigData {
		int column;
		int rows;
		int numOfMines;
	};
	FileLoading();
	// TODO copy contructor
	// TODO copy assignment
	~FileLoading();
	static ConfigData staticConfigData;
	ConfigData* configData;
	enum fileTypeToLoad {config, board};
	void loadFileHelper(string fileName, fileTypeToLoad type);
};
