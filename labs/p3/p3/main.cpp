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

int main()
{
    GameLogic gameLogic;
    Render render;
    TextureSpriteManager textureSpriteManager;

    textureSpriteManager.LoadAllTextures();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Jon Trost RuleZ");
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

        window.clear();
        // RENDER RENDER
        render.updateAndDisplayBoard(gameLogic.tileInfo, gameLogic.gameData.numOfTiles, window, textureSpriteManager);

        window.display();
    }
    return 0;
}