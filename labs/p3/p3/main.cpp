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
    sf::RenderWindow window;
    GameLogic gameLogic;
    Render render;
    render.windowSize(gameLogic.gameData.columns, gameLogic.gameData.rows, window);
    TextureSpriteManager textureSpriteManager;

    textureSpriteManager.LoadAllTextures();

    int heightOfMenu = 88;
    int lengthOfTile = 32;
    sf::Sprite test1 = textureSpriteManager.GetSprite("number_1");

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
                        test1.setPosition(mousePos.x, mousePos.y);

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
        render.updateAndDisplayBoard(gameLogic.tileInfo, gameLogic.gameData, window, textureSpriteManager);
        
        window.draw(test1);

        window.display();
    }
    return 0;
}