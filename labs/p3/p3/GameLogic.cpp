#include "GameLogic.h"

GameLogic::TileInfo* tileInfo;


GameLogic::GameLogic() {
    loadGameData();
    cout << "success" << endl;
}

GameLogic::~GameLogic() {
    if (tileInfo == nullptr) {}
    else {
        delete[] tileInfo;
    }
}


void GameLogic::loadTestBoard(TileInfo tiles[], string testBoardString)
{
    // If chosen to load test board. 
    for (int i = 0; i < gameData.numOfTiles; i++) {
        if (testBoardString[i] == '0') {
            tiles[i].mine = 0;
        }
        else tiles[i].mine = 1;
    }
}

void GameLogic::zeroBoard(TileInfo tileInfo[])
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < gameData.numOfTiles; i++) {
        x = i % gameData.columns;
        y = i / gameData.columns;
        tileInfo[i].xPos = (x * gameData.lengthOfTile);
        tileInfo[i].yPos = (y * gameData.lengthOfTile);
        tileInfo[i].revealed = 0;
        tileInfo[i].numOfMines = 0;
        tileInfo[i].flag = 0;
        tileInfo[i].mine = 1;
    }
}

void GameLogic::leftClick(int x, int y)
{
	int columnClicked = x / gameData.lengthOfTile;
	int rowClicked = y / gameData.lengthOfTile;
	cout << "Column is: " << columnClicked << " Row is: " << rowClicked << endl;
	int cellClicked = (rowClicked * gameData.columns) + columnClicked;
	if (tileInfo[cellClicked].revealed == 0) {
		tileInfo[cellClicked].revealed = 1;
	}
	else {
        // You cannot undo reveal
	}
}

void GameLogic::rightClick(int x, int y)
{
	int columnClicked = x / gameData.lengthOfTile;
	int rowClicked = y / gameData.lengthOfTile;
	int cellClicked = (rowClicked * gameData.columns) + columnClicked;
	cout << "Column is: " << columnClicked << " Row is: " << rowClicked << endl;
	if (tileInfo[cellClicked].flag == 0) {
		tileInfo[cellClicked].flag = 1;
		cout << "Num Of mines: " << (short)tileInfo[cellClicked].numOfMines << endl;
	}
	else {
		tileInfo[cellClicked].flag = 0;
	}
}

void GameLogic::loadGameData()
{
    FileLoading fileLoader;
    fileLoader.loadFileHelper("config", fileLoader.config);
    gameData.rows = fileLoader.configData->rows;
    gameData.columns = fileLoader.configData->column;
    gameData.numOfMines = fileLoader.configData->numOfMines;
    gameData.numOfTiles = (gameData.rows * gameData.columns);
    gameData.showMines = 0;
    gameData.smileyFace = 0;

    tileInfo = new TileInfo[gameData.numOfTiles];
    zeroBoard(tileInfo);
    setUpAdjacentTiles(tileInfo);
}


void GameLogic::setUpAdjacentTiles(TileInfo tileInfo[])
{
    int x = 0;
    int y = 0;
    // Setup pointers and count Mines $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    for (int i = 0; i < gameData.numOfTiles; i++) {
        x = i % gameData.columns;
        y = i / gameData.columns;
        // Set up pointers to adjacent tiles

        // Most common case
        if (x != 0 && x != gameData.columns - 1 && y != 0 && y!= gameData.rows- 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns + 1]);
        }
        // Top Left Corner
        else if (x == 0 && y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns + 1]);
        }
        // Top Right Corner
        else if (x == gameData.columns && y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
        }
        // Bottom Left Corner
        else if (x == 0 && y == gameData.columns - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
        }
        // Bottom Right Corner
        else if (x == gameData.columns - 1 && y == gameData.rows - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
        }
        // Left Edge
        else if (x == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns + 1]);
        }
        // Rigth Edge
        else if (x == gameData.columns - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
        }
        // Bottom Edge
        else if (y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + gameData.columns + 1]);
        }
        // Top Edge
        else if (y == gameData.rows - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - gameData.columns + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
        }

        int size = tileInfo[i].adjacentTiles.size();
        for (int j = 0; j < size; j++) {
            if (tileInfo[i].adjacentTiles.at(j)->mine == 1) {
                tileInfo[i].numOfMines++;
            }
        }
    }
}
