#include "LoadConfig.h"

FileLoading::ConfigData staticConfigData;

FileLoading::FileLoading() {
	configData = new ConfigData;
}

void FileLoading::loadFileHelper(std::string fileName, fileTypeToLoad type) {
	std::string path = "boards/";
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

void FileLoading::loadConfig(std::string path) {
	fstream fileIn(path);
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
	fileIn.close();
}

void FileLoading::loadBoard(std::string path) {
	fstream fileIn(path);
	std::string buffer;
	if (fileIn.is_open()) {
		while (getline(fileIn, buffer)) {
			testBoardString += buffer;
		}
	}
	else {
		cout << "ERROR: " << path << " did not open." << endl;
	}
	fileIn.close();
}

void FileLoading::readPNGfile(string fileName) {
	string path = "../images";
	path += fileName + ".cfg";
	int size = 8;
	textureData = new unsigned char[size];
	fstream fileInput;
	fileInput.open(path, std::ios_base::in | std::ios_base::binary);
	for (int i = 0; i < size; i++) {
		fileInput.read((char*)textureData[i], sizeof(char));
	}
	for (int i = 0; i < size; i++) {
		cout << textureData[i] << " ";
	}
	cout << endl;
	fileInput.close();
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
