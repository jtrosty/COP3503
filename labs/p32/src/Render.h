#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "TextureSpriteManager.h"

class Render {

    int digitOffset(char digit, int offset);
    void displayNumOfMines(const GameLogic::TileInfo& tileInfo,
                            const TextureSpriteManager& textureSpriteManager,
                            sf::RenderWindow& window);    

    void userInterface(GameLogic::GameData gameData, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window);
    void mineCounter(GameLogic::GameData gameData, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window);

    public:
    void updateAndDisplayBoard(GameLogic::TileInfo tileInfo[],
                               GameLogic::GameData& gameData,
                               sf::RenderWindow& window, 
                               TextureSpriteManager& textureSpriteManager);
    void windowSize(int columns, int rows, sf::RenderWindow& window);

};