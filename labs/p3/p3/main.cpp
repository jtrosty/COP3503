#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureSpriteManager.h"
#include "LoadConfig.h"
#include "Random.h"
#include <vector>
#include "GameLogic.h"
#include "Render.h"

using std::cout;
using std::endl;
/************************************************************************************
    The heart of the program are 2 structs contained within game logic:
           GameData and TileInfo
    1. GameData is made 1 time. TileInfo is turned into a array based on the number of
    tiles required (contained in GameData struct).
    2. GameLogic sets up GameData and TileInfo.
        2.a See 'loadGameData' for setup of GameData
        2.b TileInfo[] gets zeroed
        2.c TileInfo[] gets random mines added
        3.d TileInfo[] has the adjacentTile vector setup and so each tile has a pointer 
        to it's neighbors.
    3. Render than takes both structs and uses them to draw to the board. 
    4. Game logic takes user input and modifies the TileInfo[] based on the user input. 

    LoadConfig loads other boards and config files, GameLogic applies the data to the
    Game Data file.

    TextureSprite manager handles 'textures' and 'sprites' so that 'Render' may pull 
    them for drawing. 


*************************************************************************************/

int main()
{
    sf::RenderWindow window;
    GameLogic gameLogic;
    Render render;
    render.windowSize(gameLogic.gameData.columns, gameLogic.gameData.rows, window);
    TextureSpriteManager textureSpriteManager;

    textureSpriteManager.LoadAllTextures();

    int heightOfMenu = 88;
    int lengthOfTile = 32;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                //      // window closed
				case sf::Event::Closed:
					window.close();
					break;

				// Mouse Button Pressed
                case sf::Event::MouseButtonPressed: 
                    if (event.key.code == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        gameLogic.leftClick(mousePos.x, mousePos.y);
                    }
                    else if (event.key.code == sf::Mouse::Right) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        gameLogic.rightClick(mousePos.x, mousePos.y);
                    } 
			        break;
			    // we don't process other types of events
				default:
					break;
            }
        }

        window.clear(sf::Color(255, 255, 255));

        // RENDER RENDER
        render.updateAndDisplayBoard(gameLogic.tileInfo, gameLogic.gameData, window, textureSpriteManager);
        window.display();
    }

    return 0;
}