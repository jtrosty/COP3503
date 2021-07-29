#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
#include "TextureSpriteManager.h"

class Render {

    void displayNumOfMines(GameLogic::TileInfo& tileInfo, 
                           TextureSpriteManager& textureSpriteManager,
                           sf::RenderWindow& window, 
                           sf::Sprite& numberOfMines);

    public:
    void updateAndDisplayBoard(GameLogic::TileInfo tileInfo[],
                               int numOftiles,
                               sf::RenderWindow& window, 
                               TextureSpriteManager& textureSpriteManager);
};