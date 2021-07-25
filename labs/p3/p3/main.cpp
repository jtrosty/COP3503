#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureSpriteManager.h"
#include "LoadConfig.h"
#include "Random.h"
#include <vector>

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

    //Load textures
    TextureSpriteManager textureSpriteManager;
    textureSpriteManager.LoadAllTextures();


    // DRAW THE BOARD:
    // 
    //Config file
    ////////////////////////////////////////////////// Creates tile data
    FileLoading fileLoader;
    fileLoader.loadFileHelper("config", fileLoader.config);
    fileLoader.loadFileHelper("testboard1", fileLoader.board);

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
        tileInfo[i].xPos = (x * lengthOfTile);
        tileInfo[i].yPos = (y * lengthOfTile);
        tileInfo[i].revealed = 0;
        tileInfo[i].numOfMines = 0;
        tileInfo[i].flag = 0;
        tileInfo[i].mine = 1;
    }

    // Add mines to tiles ##########################################################
    // Make it Random


    // If chosen to load test board. 
    for (int i = 0; i < numOfTiles; i++) {
        if (fileLoader.testBoardString[i] == '0') {
            tileInfo[i].mine = 0;
        }
        else tileInfo[i].mine = 1;
    }

    // Setup pointers and count Mines $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    for (int i = 0; i < numOfTiles; i++) {
        x = i % fileLoader.configData->column;
        y = i / fileLoader.configData->column;
        // Set up pointers to adjacent tiles

        // Most common case
        if (x != 0 && x != fileLoader.configData->column - 1 && y != 0 && y!= fileLoader.configData->rows - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column + 1]);
        }
        // Top Left Corner
        else if (x == 0 && y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column + 1]);
        }
        // Top Right Corner
        else if (x == fileLoader.configData->column && y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
        }
        // Bottom Left Corner
        else if (x == 0 && y == fileLoader.configData->column - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
        }
        // Bottom Right Corner
        else if (x == fileLoader.configData->column - 1 && y == fileLoader.configData->rows - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
        }
        // Left Edge
        else if (x == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column + 1]);
        }
        // Rigth Edge
        else if (x == fileLoader.configData->column - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
        }
        // Bottom Edge
        else if (y == 0) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + fileLoader.configData->column + 1]);
        }
        // Top Edge
        else if (y == fileLoader.configData->rows - 1) {
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - fileLoader.configData->column + 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i - 1]);
            tileInfo[i].adjacentTiles.push_back(&tileInfo[i + 1]);
        }

        int size = tileInfo[i].adjacentTiles.size();
        for (int j = 0; j < size; j++) {
            if (tileInfo[i].adjacentTiles.at(j)->mine == 1) {
                tileInfo[i].numOfMines++;
            }
        }
    }
    
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

				// key pressed
                case sf::Event::MouseButtonPressed: 
                    if (event.key.code == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        textureSpriteManager.GetSprite("test_3").setPosition(mousePos.x, mousePos.y);
                        //cout << "X is: " << mousePos.x << " Y is: " << mousePos.y << endl;

                        int columnClicked = mousePos.x / lengthOfTile;
                        int rowClicked = mousePos.y / lengthOfTile;
                        cout << "Column is: " << columnClicked << " Row is: " << rowClicked << endl;
                        int cellClicked = (rowClicked * fileLoader.configData->column) + columnClicked;
                        if (tileInfo[cellClicked].revealed == 0) {
                            tileInfo[cellClicked].revealed = 1;
                        }
                        else {
                            tileInfo[cellClicked].revealed = 0;
                        }
                    }
                    else if (event.key.code == sf::Mouse::Right) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        textureSpriteManager.GetSprite("test_3").setPosition(mousePos.x, mousePos.y);
                        //cout << "X is: " << mousePos.x << " Y is: " << mousePos.y << endl;

                        int columnClicked = mousePos.x / lengthOfTile;
                        int rowClicked = mousePos.y / lengthOfTile;
                        int cellClicked = (rowClicked * fileLoader.configData->column) + columnClicked;
                        cout << "Column is: " << columnClicked << " Row is: " << rowClicked << endl;
                        if (tileInfo[cellClicked].flag == 0) {
                            tileInfo[cellClicked].flag = 1;
                            cout << "Num Of mines: " << (short)tileInfo[cellClicked].numOfMines << endl;
                        }
                        else {
                            tileInfo[cellClicked].flag = 0;
                        }
                    } 
			        break;
			    // we don't process other types of events
				default:
					break;
            }
            /*
            if (event.type == sf::Event::Closed)
                window.close();
            }
            */
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
    delete[] tileInfo;
    return 0;
}