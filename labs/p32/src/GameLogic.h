#pragma once
#include <string>
#include <vector>
#include "Random.h"
#include "Fileloader.h"
#include "Draw.h"

class GameLogic
{

public:

    struct GameData {
        int rows;
        int columns;
        int numOfMines;
        int numOfFlags;
        int numOfTiles;
        short lengthOfTile = 32; // Magic number
        short sizeOfInterfaceTiles = 64; // Magic number
        char smileyFace;
        char showMines; // I use this as a int, just with 1 byte. 
        int smileX;
        int test_1X;
        int test_2X;
        int test_3X;
        int debug_ShowMinesX;
        char debugShowMine;
        char winLose; // If 'P' -play, 'W' -YOU WIN!, 'L' - You lose =(
    };

    struct TileInfo {
        int xPos; // location of each tile
        int yPos;
        char revealed; // 0 - not revealed, 1 - revealed
        char mine; // 0 - no mine, 1 - mine
        char flag; // 0 - no flag, 1 - flag
        char numOfMines; // 1-8 then that is num of mines, or >8 has mine
        std::vector<TileInfo*> adjacentTiles; // Containers to other mines. 
    };
    TileInfo* tileInfo;
    GameData gameData;
    FileLoader fileLoader;

    void checkIfWinner();
    void showMines();
    void resetGame(TileInfo tileInfo[]);
    void userInterfaceControls(int x, int y);
    void randomMines(TileInfo tileInfo[], GameData& gameData);
    void emptyTileAutoOpen(TileInfo& tile);
    void setUpAdjacentTiles(TileInfo tiles[]);
    void loadTestBoard(TileInfo tiles[], string testBoard);
	void zeroBoard(TileInfo tiles[]);
    void loadGameData();
	//void restartGame();
    void leftClick(int x, int y);
    void rightClick(int x, int y);
    void checkUserInput();

    // Contructor
    GameLogic();

    // Destructor
    ~GameLogic();
};