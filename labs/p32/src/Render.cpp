#include "Render.h"

void Render::updateAndDisplayBoard(GameLogic& gameLogic,
                                   Draw& draw, 
                                   FileLoader& fileLoader, 
                                   RenderBuffer& buffer) {
    ////////////////////////////////////////////////////////////////////////////////
    // Draw Sprites
	//userInterface(gameData, fileLoader, draw);
	//mineCounter(gameData, fileLoader, draw);
    FileLoader::TextureData* hidden = &fileLoader.getTextureBMP("tile_hidden");
    FileLoader::TextureData* mine = &fileLoader.getTextureBMP("mine");
    FileLoader::TextureData* revealed = &fileLoader.getTextureBMP("tile_revealed");
    FileLoader::TextureData* flag = &fileLoader.getTextureBMP("flag");
	for (int i = 0; i < gameLogic.gameData.numOfTiles; i++) {
		if (gameLogic.tileInfo[i].revealed == 0) {
            draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *hidden, buffer);
			if (gameLogic.tileInfo[i].flag != 0) {
                draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *flag, buffer);
			}
		}
		else {
            draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *revealed, buffer);
			if (gameLogic.tileInfo[i].mine != 0) {
                draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *mine, buffer);
			}
			else {
				//displayNumOfMines(gameLogic.tileInfo[i], fileLoader, draw); //*numberOfMines);
			}
		}
		if (gameLogic.gameData.debugShowMine == 1) {
			if (gameLogic.tileInfo[i].mine == 1) {
                draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *mine, buffer);
				if (gameLogic.gameData.winLose == 'W') {
                    draw.drawTexture(gameLogic.tileInfo[i].xPos, gameLogic.tileInfo[i].yPos, *flag, buffer);
				}
			}
		}
    }
}
/*
void Render::userInterface(GameLogic::GameData gameData, FileLoader& fileLoader, Draw& draw) {
	
	// Happy face
    FileLoader::TextureData smiley = fileLoader.GetSprite("face_happy");
	// Center of width offset by widht of smileyface (64 pixels)
	int xPos = gameData.smileX;
	int yPos = (gameData.rows * gameData.lengthOfTile);
	
	if (gameData.winLose == 'P') {
		smiley = fileLoader.GetSprite("face_happy");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}
	else if (gameData.winLose == 'L') {
		smiley = fileLoader.GetSprite("face_lose");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}
	else if (gameData.winLose == 'W') {
		smiley = fileLoader.GetSprite("face_win");
		smiley.setPosition(xPos, yPos);
		window.draw(smiley);
	}

	// Test #1 #2 and #2
	// yPos doesnt' have to change
	// Test 3 draw
	FileLoader::TextureData testIcon = fileLoader.GetSprite("test_3");
	xPos = gameData.test_3X;
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
	// Test 2 draw
	xPos = gameData.test_2X;
	testIcon = fileLoader.GetSprite("test_2");
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
	// Test 1 draw
	xPos = gameData.test_1X;
	testIcon = fileLoader.GetSprite("test_1");
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
	xPos = gameData.debug_ShowMinesX;
	testIcon = fileLoader.GetSprite("debug");
	testIcon.setPosition(xPos, yPos);
	window.draw(testIcon);
}

void Render::mineCounter(GameLogic::GameData gameData, FileLoader& fileLoader, Draw& draw) {
	int sizeOfDigit = 21;
	int counter = gameData.numOfMines - gameData.numOfFlags;
	std::string counterStr = std::to_string(std::abs(counter));
	//cout << "coutner string: " << counterStr << endl;
	FileLoader::TextureData* digits = &fileLoader.GetSprite("digits");
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

void Render::windowSize(int columns, int rows, Draw& draw){
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

void Render::displayNumOfMines(const GameLogic::TileInfo& tileInfo,
								const FileLoader& fileLoader,
							 	Draw& draw) {
	FileLoader::TextureData* numberOfMines;
    switch ((short)tileInfo.numOfMines) {
		case 1:
			numberOfMines = &fileLoader.GetSprite("number_1");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 2:
			numberOfMines = &fileLoader.GetSprite("number_2");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 3:
			numberOfMines = &fileLoader.GetSprite("number_3");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 4:
			numberOfMines = &fileLoader.GetSprite("number_4");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 5:
			numberOfMines = &fileLoader.GetSprite("number_5");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 6:
			numberOfMines = &fileLoader.GetSprite("number_6");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 7:
			numberOfMines = &fileLoader.GetSprite("number_7");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
			break;
		case 8:
			numberOfMines = &fileLoader.GetSprite("number_8");
			numberOfMines->setPosition(tileInfo.xPos, tileInfo.yPos);
			window.draw(*numberOfMines);
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
*/