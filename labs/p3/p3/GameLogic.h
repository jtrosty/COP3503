#pragma once
#include <string>
#include <vector>
#include"LoadConfig.h"

class GameLogic
{
public:

    struct GameData {
        int rows;
        int columns;
        int numOfMines;
        int numOfTiles;
        short lengthOfTile = 32;
        short sizeOfInterfaceTiles = 64;
        char smileyFace;
        char showMines;
    };

    struct TileInfo {
        int xPos;
        int yPos;
        char revealed;
        char mine;
        char flag;
        char numOfMines; // 1-8 then that is num of mines, or >8 has mine
        std::vector<TileInfo*> adjacentTiles;
    };
    TileInfo* tileInfo;
    GameData gameData;

    void setUpAdjacentTiles(TileInfo tiles[]);
    void loadTestBoard(TileInfo tiles[], string testBoard);
	void zeroBoard(TileInfo tiles[]);
    void loadGameData();
	//void restartGame();
    void leftClick(int x, int y);
    void rightClick(int x, int y);

    // Contructor
    GameLogic();

    // Destructor
    ~GameLogic();
};

