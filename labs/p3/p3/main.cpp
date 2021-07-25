#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureSpriteManager.h"
#include "LoadConfig.h"
#include "Random.h"
#include <vector>
#include "GameLogic.h"


using std::cout;
using std::endl;

int main()
{
    struct TileInfo {
        int xPos;
        int yPos;
        char revealed;
        char mine;
        char flag;
        char numOfMines; // 1-8 then that is num of mines, or >8 has mine
        std::vector<TileInfo*> adjacentTiles;
    };

    GameLogic gameLogic;

    //Load textures
    TextureSpriteManager textureSpriteManager;
    textureSpriteManager.LoadAllTextures();


    // DRAW THE BOARD:

    int heightOfMenu = 88;
    int lengthOfTile = 32;

    //int totalWidth = lengthOfTile * fileLoader.configData->column;
    //int totalHeight = (lengthOfTile * fileLoader.configData->rows) + heightOfMenu;

    // Add mines to tiles ##########################################################
    // Make it Random


    
    // Determine Number of mines nearby

    /// <summary>
    /// /////////////////////////////////////////setup window
    /// </summary>
    /// <returns></returns>
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Jon Trost RuleZ");


    
    // DELETE DELETE DELETE
    // Random Test
    int randomX = Random::Int(0, 400);

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

        window.clear();

		/// <summary>
		/// /////////////////////////////// display stuff
		/// </summary>
		sf::Sprite tileSprite = textureSpriteManager.GetSprite("mine");
		int xPos = 0;
		int yPos = 0;
		for (int i = 0; i < fileLoader.configData->rows; i++) {
			for (int j = 0; j < fileLoader.configData->column; j++) {
				tileSprite.setPosition(xPos, yPos);
				window.draw(tileSprite);
				xPos += lengthOfTile;
			}
            xPos = 0;
			yPos += lengthOfTile;
		}
        ////////////////////////////////////////////////////////////////////////////////
        // Draw Sprites
        sf::Sprite* hidden = &textureSpriteManager.GetSprite("tile_hidden");
        sf::Sprite* mine = &textureSpriteManager.GetSprite("mine");
        sf::Sprite* revealed = &textureSpriteManager.GetSprite("tile_revealed");
        sf::Sprite* flag = &textureSpriteManager.GetSprite("flag");
        sf::Sprite* numberOfMines;
		for (int i = 0; i < numOfTiles; i++) {
            if (tileInfo[i].revealed == 0) {
                hidden->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
                window.draw(*hidden);
                if (tileInfo[i].flag != 0) {
					flag->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
					window.draw(*flag);
                }
            }
            else {
                revealed->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
                window.draw(*revealed);
                if (tileInfo[i].mine != 0) {
                    mine->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
                    window.draw(*mine);
                }
                else {
                    switch (tileInfo[i].numOfMines) {
						case 1:
                            numberOfMines = &textureSpriteManager.GetSprite("number_1");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 2:
                            numberOfMines = &textureSpriteManager.GetSprite("number_2");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 3:
                            numberOfMines = &textureSpriteManager.GetSprite("number_3");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 4:
                            numberOfMines = &textureSpriteManager.GetSprite("number_4");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 5:
                            numberOfMines = &textureSpriteManager.GetSprite("number_5");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 6:
                            numberOfMines = &textureSpriteManager.GetSprite("number_6");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 7:
                            numberOfMines = &textureSpriteManager.GetSprite("number_7");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						case 8:
                            numberOfMines = &textureSpriteManager.GetSprite("number_8");
							numberOfMines->setPosition(tileInfo[i].xPos, tileInfo[i].yPos);
							window.draw(*numberOfMines);
							break;
						default:
							break;
                    }
                    // NEED TO ADD THE LOGIC FOR DISPLAYING THE NUM OF MINES
                }
            }
		}
        ////////////////////////////////////////////////////////////////////////////////////

        window.display();
    }
    return 0;
}