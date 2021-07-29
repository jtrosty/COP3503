#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "TextureSpriteManager.h"

class Render {

    void displayNumOfMines(GameLogic::TileInfo& tileInfo,
                           TextureSpriteManager& textureSpriteManager,
                           sf::RenderWindow& window, 
                           sf::Sprite& numberOfMines);
    
    void userInterface(GameLogic::GameData gameData, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window);

    public:
    void updateAndDisplayBoard(GameLogic::TileInfo tileInfo[],
                               GameLogic::GameData& gameData,
                               sf::RenderWindow& window, 
                               TextureSpriteManager& textureSpriteManager);
    void windowSize(int columns, int rows, sf::RenderWindow& window);

};