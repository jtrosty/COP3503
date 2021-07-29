#include "Render.h"
#include "TextureSpriteManager.h"
#include "GameLogic.h"
#include <math.h>

void Render::updateAndDisplayBoard(GameLogic::TileInfo tileInfo[],
								   GameLogic::GameData& gameData,
                                   sf::RenderWindow& window, 
                                   TextureSpriteManager& textureSpriteManager) {
    ////////////////////////////////////////////////////////////////////////////////
    // Draw Sprites
	userInterface(gameData, textureSpriteManager, window);
	mineCounter(gameData, textureSpriteManager, window);
    sf::Sprite* hidden = &textureSpriteManager.GetSprite("tile_hidden");
    sf::Sprite* mine = &textureSpriteManager.GetSprite("mine");
    sf::Sprite* revealed = &textureSpriteManager.GetSprite("tile_revealed");
    sf::Sprite* flag = &textureSpriteManager.GetSprite("flag");
    sf::Sprite* numberOfMines = &textureSpriteManager.GetSprite("number_1");
    for (int i = 0; i < gameData.numOfTiles; i++) {
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
            }
        }
    }
}

void Render::userInterface(GameLogic::GameData gameData, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window) {
	
	// Happy face
    sf::Sprite smiley = textureSpriteManager.GetSprite("face_happy");
	// Center of width offset by widht of smileyface (64 pixels)
	int xPos = (((gameData.columns * gameData.lengthOfTile) - (gameData.sizeOfInterfaceTiles)) / 2);
	int yPos = (gameData.rows * gameData.lengthOfTile);
	//window.draw(smiley);
	
	if (gameData.smileyFace == 0) {
		smiley = textureSpriteManager.GetSprite("face_happy");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}
	else if (gameData.smileyFace == 1) {
		smiley = textureSpriteManager.GetSprite("face_lose");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}
	else {
		smiley = textureSpriteManager.GetSprite("face_win");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}

	// Test #1 #2 and #2
	// yPos doesnt' have to change
	// Test 3 draw
	sf::Sprite testIcon = textureSpriteManager.GetSprite("test_3");
	xPos = (gameData.columns * gameData.lengthOfTile) - gameData.sizeOfInterfaceTiles;
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
	// Test 2 draw
	xPos = xPos - gameData.sizeOfInterfaceTiles;
	testIcon = textureSpriteManager.GetSprite("test_2");
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
	// Test 1 draw
	xPos = xPos - gameData.sizeOfInterfaceTiles;
	testIcon = textureSpriteManager.GetSprite("test_1");
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
}

void Render::mineCounter(GameLogic::GameData gameData, TextureSpriteManager& textureSpriteManager, sf::RenderWindow& window) {
	int sizeOfDigit = 21;
	int counter = gameData.numOfMines - gameData.numOfFlags;
	std::string counterStr = std::to_string(std::abs(counter));
	//cout << "coutner string: " << counterStr << endl;
	sf::Sprite* digits = &textureSpriteManager.GetSprite("digits");
	sf::Vector2f rectSize(sizeOfDigit, gameData.lengthOfTile);
	int yPos = (gameData.rows * gameData.lengthOfTile);
	int xPos = sizeOfDigit;
	int xDigit = 0;
	short size = counterStr.size();

	if (counter < 0) {
		xDigit = digitOffset('-', sizeOfDigit);
		digits->setTextureRect(sf::IntRect(xDigit, 0, 21, 32));
		digits->setPosition(0, yPos);
		window.draw(*digits);
	}
	if (size == 1) {
		xDigit = digitOffset('0', sizeOfDigit);
		digits->setTextureRect(sf::IntRect(xDigit, 0, 21, 32));
		digits->setPosition(xPos, yPos);
		window.draw(*digits);
		xPos += 21;
		digits->setPosition(xPos, yPos);
		window.draw(*digits);
		xPos += 21;
	}
	if (size == 2) {
		xDigit = digitOffset('0', sizeOfDigit);
		digits->setTextureRect(sf::IntRect(xDigit, 0, 21, 32));
		digits->setPosition(xPos, yPos);
		window.draw(*digits);
		xPos += 21;
	}

	for (int i = 0; i < size; i++) {
		xDigit = digitOffset(counterStr[i], sizeOfDigit);

		digits->setTextureRect(sf::IntRect(xDigit, 0, 21, 32));
		digits->setPosition(xPos, yPos);
		window.draw(*digits);
		xPos += 21;
	}
}

void Render::windowSize(int columns, int rows, sf::RenderWindow& window){
	int minColumns = 22;
	short textureWidth = 32;
	short heightUI = 88;

	if (columns < minColumns);
	else minColumns = columns;
	
	int windowWidth = minColumns * textureWidth;
	int windowHeight = (rows * textureWidth) + heightUI;

	window.create(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
	window.clear(sf::Color::White);
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

int Render::digitOffset(char digit, int offset) {
	switch (digit) {
	case '0':
		return 0;
		break;
	case '1':
		return offset;
		break;
	case '2':
		return offset * 2;
		break;
	case '3':
		return offset * 3;
		break;
	case '4':
		return offset * 4;
		break;
	case '5':
		return offset * 5;
		break;
	case '6':
		return offset * 6;
		break;
	case '7':
		return offset * 7;
		break;
	case '8':
		return offset * 8;
		break;
	case '9':
		return offset * 9;
		break;
	case '-':
		return offset * 10;
		break;
	}
}
