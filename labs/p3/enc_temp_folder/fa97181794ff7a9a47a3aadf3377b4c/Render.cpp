#include "Render.h"
#include "TextureSpriteManager.h"
#include "GameLogic.h"

void Render::updateAndDisplayBoard(GameLogic::TileInfo tileInfo[],
                                   int numOfTiles,
                                   sf::RenderWindow& window, 
                                   TextureSpriteManager& textureSpriteManager) {
    ////////////////////////////////////////////////////////////////////////////////
    // Draw Sprites
    sf::Sprite* hidden = &textureSpriteManager.GetSprite("tile_hidden");
    sf::Sprite* mine = &textureSpriteManager.GetSprite("mine");
    sf::Sprite* revealed = &textureSpriteManager.GetSprite("tile_revealed");
    sf::Sprite* flag = &textureSpriteManager.GetSprite("flag");
    sf::Sprite* numberOfMines = &textureSpriteManager.GetSprite("number_1");
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
                // ****************************** FOR TESTING
                displayNumOfMines(tileInfo[i], textureSpriteManager, window, *numberOfMines);
            }
            else {
                displayNumOfMines(tileInfo[i], textureSpriteManager, window, *numberOfMines);
                // NEED TO ADD THE LOGIC FOR DISPLAYING THE NUM OF MINES
                /*
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
        */
            }
        }
    }
}

void Render::displayNumOfMines(GameLogic::TileInfo& tileInfo, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window, sf::Sprite& numberOfMines) {

    switch (tileInfo.numOfMines) {
		case 1:
			numberOfMines = textureSpriteManager.GetSprite("number_1");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 2:
			numberOfMines = textureSpriteManager.GetSprite("number_2");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 3:
			numberOfMines = textureSpriteManager.GetSprite("number_3");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 4:
			numberOfMines = textureSpriteManager.GetSprite("number_4");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 5:
			numberOfMines = textureSpriteManager.GetSprite("number_5");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 6:
			numberOfMines = textureSpriteManager.GetSprite("number_6");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 7:
			numberOfMines = textureSpriteManager.GetSprite("number_7");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		case 8:
			numberOfMines = textureSpriteManager.GetSprite("number_8");
			numberOfMines.setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(numberOfMines);
			break;
		default:
			break;
    }
}

