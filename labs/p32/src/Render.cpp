#include "Render.h"

void Render::updateAndDisplayBoard(GameLogic& gameLogic,
                                   Draw& draw, 
                                   FileLoader& fileLoader, 
                                   RenderBuffer& buffer) {
    ////////////////////////////////////////////////////////////////////////////////
    // Draw Sprites
	userInterface(gameLogic.gameData, fileLoader, draw, buffer);
	mineCounter(gameLogic.gameData, fileLoader, draw, buffer);
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

void Render::userInterface(GameLogic::GameData& gameData, FileLoader& fileLoader, Draw& draw, RenderBuffer& buffer) {
	// Happy face
    FileLoader::TextureData* smiley; //= &fileLoader.getTextureBMP("face_happy");
	// Center of width offset by widht of smileyface (64 pixels)
	int xPos = gameData.smileX;
	int yPos = (gameData.rows * gameData.lengthOfTile);
	
	if (gameData.winLose == 'P') {
		smiley = &fileLoader.getTextureBMP("face_happy");
    	draw.drawTexture(xPos, yPos, *smiley, buffer);
	}
	else if (gameData.winLose == 'L') {
		smiley = &fileLoader.getTextureBMP("face_lose");
    	draw.drawTexture(xPos, yPos, *smiley, buffer);
	}
	else if (gameData.winLose == 'W') {
		smiley = &fileLoader.getTextureBMP("face_win");
    	draw.drawTexture(xPos, yPos, *smiley, buffer);
	}

	// Test #1 #2 and #2
	// yPos doesnt' have to change
	// Test 3 draw
	FileLoader::TextureData* testIcon = &fileLoader.getTextureBMP("test_3");
	xPos = gameData.test_3X;
    draw.drawTexture(xPos, yPos, *testIcon, buffer);
	// Test 2 draw
	xPos = gameData.test_2X;
	testIcon = &fileLoader.getTextureBMP("test_2");
    draw.drawTexture(xPos, yPos, *testIcon, buffer);
	// Test 1 draw
	xPos = gameData.test_1X;
	testIcon = &fileLoader.getTextureBMP("test_1");
    draw.drawTexture(xPos, yPos, *testIcon, buffer);
	xPos = gameData.debug_ShowMinesX;
	testIcon = &fileLoader.getTextureBMP("debug");
    draw.drawTexture(xPos, yPos, *testIcon, buffer);
}

void Render::mineCounter(GameLogic::GameData& gameData, FileLoader& fileLoader, Draw& draw, RenderBuffer& buffer) {
	int sizeOfDigit = 21;
	int counter = 000;//gameData.numOfMines - gameData.numOfFlags;
	std::string counterStr = std::to_string(std::abs(counter));
	FileLoader::TextureData* digits = &fileLoader.getTextureBMP("digits");

	// x0, will be pulled from digit offset function
	Rect subTextureNum;
	subTextureNum.x1 = 21; // Width in X
	subTextureNum.y0 = 0;
	subTextureNum.y1 = 32; // Width in Y
	
	// (sizeOfDigit, game.LenghtOfTile);
	int yPos = (gameData.rows * gameData.lengthOfTile);
	int xPos = sizeOfDigit;
	int xDigit = 0;
	short size = counterStr.size();

	if (counter < 0) {
		subTextureNum.x0 = digitOffset('-', sizeOfDigit);
    	draw.drawTextureSubRectangle(xPos, yPos, subTextureNum, *digits, buffer);
	}
	if (size == 1) {
		subTextureNum.x0 = digitOffset('0', sizeOfDigit);
    	draw.drawTextureSubRectangle(xPos, yPos, subTextureNum, *digits, buffer);
		xPos += 21;
    	draw.drawTextureSubRectangle(xPos, yPos, subTextureNum, *digits, buffer);
		xPos += 21;
	}
	if (size == 2) {
		subTextureNum.x0 = digitOffset('0', sizeOfDigit);
    	draw.drawTextureSubRectangle(xPos, yPos, subTextureNum, *digits, buffer);
		xPos += 21;
	}

	for (int i = 0; i < size; i++) {
		subTextureNum.x0 = digitOffset(counterStr[i], sizeOfDigit);
    	draw.drawTextureSubRectangle(xPos, yPos, subTextureNum, *digits, buffer);
		xPos += 21;
	}
}

/*
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
*/

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
	default: 
		return 0;
		break;
	}
}