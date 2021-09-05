#pragma once
#include "GameLogic.h"
#include "draw.h"
#include "FileLoader.h"
#include "utils.h"

class Render {

    int digitOffset(char digit, int offset);
    //void displayNumOfMines(const GameLogic::TileInfo& tileInfo,
     //                       const FileLoader& fileLoader,
      //                      Draw& draw);    

    void userInterface(GameLogic::GameData& gameData, FileLoader& fileLoader, Draw& draw, RenderBuffer& buffer);
    void mineCounter(GameLogic::GameData& gameData, FileLoader& fileLoader, Draw& draw, RenderBuffer& buffer);

    public:
    void updateAndDisplayBoard(GameLogic& gameLogic,
                               Draw& draw, 
                               FileLoader& fileLoader,
                               RenderBuffer& buffer);
    //void drawSize(int columns, int rows, Draw& draw);

};