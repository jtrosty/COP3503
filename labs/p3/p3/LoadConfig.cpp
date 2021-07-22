#include "LoadConfig.h"

//FileLoading::ConfigData configData;

void FileLoading::loadFileHelper(string fileName, fileTypeToLoad type) {
	string path = "boards/";
	switch (type)
	{
	case FileLoading::config:
		path += fileName + ".cfg";
		loadConfig(fileName);
		break;
	case FileLoading::board:
		path += fileName + ".brd";
		break;
	default:
		break;
	}

}

void FileLoading::loadConfig(string fileName) {
	ifstream fileIn(fileName);
	int column;
	int rows;
	int numOfMines;
	fileIn >> column; 
	fileIn >> rows;
	fileIn >> numOfMines;
	//configData.column = column;
	//configData.rows = rows;
	//configData.numOfMines = numOfMines;
	//cout << configData.column << endl;
	cout << "The column is " << column << endl;

}
