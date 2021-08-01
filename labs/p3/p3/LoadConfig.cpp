#include "LoadConfig.h"

FileLoading::ConfigData staticConfigData;

FileLoading::FileLoading() {
	configData = new ConfigData;
}

void FileLoading::loadFileHelper(string fileName, fileTypeToLoad type) {
	string path = "boards/";
	switch (type)
	{
	case FileLoading::config:
		path += fileName + ".cfg";
		loadConfig(path);
		break;
	case FileLoading::board:
		path += fileName + ".brd";
		loadBoard(path);
		break;
	default:
		break;
	}
}

void FileLoading::loadConfig(string path) {
	ifstream fileIn(path);
	if (fileIn.is_open()) {
		fileIn >> configData->column;
		fileIn >> configData->rows;
		fileIn >> configData->numOfMines;

		//TODO (Jon) remove the following:
		/*
		cout << "The column is " << configData->column << endl;
		cout << "The column is " << configData->rows << endl;
		cout << "The column is " << configData->numOfMines << endl;
		*/
	}
	else {
		cout << "ERROR: " << path << " did not open." << endl;
	}
}

void FileLoading::loadBoard(string path) {
	ifstream fileIn(path);
	string buffer;
	if (fileIn.is_open()) {
		while (getline(fileIn, buffer)) {
			testBoardString += buffer;
		}
	}
	else {
		cout << "ERROR: " << path << " did not open." << endl;
	}
}

FileLoading::~FileLoading() {
	delete configData;
}

string FileLoading::getTestBoardString()
{
	return testBoardString;
}

void FileLoading::deleteTestBoardString() {
	testBoardString.clear();
}
