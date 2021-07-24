#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureSpriteManager.h"
#include "LoadConfig.h"
#include "Random.h"

using std::cout;
using std::endl;

int main()
{
    struct TileInfo {
        int xPos;
        int yPos;

        char numOfMinesOrMine; // 1-8 then that is num of mines, or >8 has mine
    };

    sf::Sprite sprite; 

    // the cirlce
    // TODO (Jon)
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //Load textures
    TextureSpriteManager textureSpriteManager;
    textureSpriteManager.LoadAllTextures();


    // DRAW THE BOARD:
    // 
    //Config file
    FileLoading fileLoader;
    fileLoader.loadFileHelper("config", fileLoader.config);

    int heightOfMenu = 88;
    int lengthOfTile = 32;

    int totalWidth = lengthOfTile * fileLoader.configData->column;
    int totalHeight = (lengthOfTile * fileLoader.configData->rows) + heightOfMenu;
    int numOfTiles = fileLoader.configData->column * fileLoader.configData->rows;
    TileInfo* tileInfo = new TileInfo[fileLoader.configData->column * fileLoader.configData->rows];
    int x = 0;
    int y = 0;
    for (int i = 0; i < numOfTiles; i++) {
        x = i % fileLoader.configData->column;
        y = i / fileLoader.configData->column;
        tileInfo->xPos = (x * lengthOfTile);
        tileInfo->yPos = (y * lengthOfTile);
        tileInfo->numOfMinesOrMine = 9;
    }

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Jon Trost RuleZ");


    cout << "column num " <<  fileLoader.configData->column << endl;
    
    // Random Test
    int randomX = Random::Int(0, 400);
    cout << randomX << endl;
   


    textureSpriteManager.GetTexture("face_happy");
    sprite.setTexture(textureSpriteManager.GetTexture("face_happy"));
    sprite.setPosition(500, 500);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                textureSpriteManager.GetSprite("test_3").setPosition(mousePos.x, mousePos.y);
                cout << "X is: " << mousePos.x << " Y is: " << mousePos.y << endl;
            }
        }

        window.clear();

		sf::Sprite tileSprite = textureSpriteManager.GetSprite("tile_hidden");
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
        sf::Sprite* hidden = &textureSpriteManager.GetSprite("tile_hidden");
        sf::Sprite* mine = &textureSpriteManager.GetSprite("mine");
        sf::Sprite* revealed = &textureSpriteManager.GetSprite("tile_revealed");
		for (int i = 0; i < fileLoader.configData->rows; i++) {

			window.draw(tileSprite);
		}

        window.draw(shape);
        window.draw(sprite);
        window.draw(textureSpriteManager.GetSprite("test_3"));
        window.display();
    }
    return 0;
}