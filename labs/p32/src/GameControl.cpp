#include "GameControl.h"

void GameControl::updateWindowAndUserInput(GameLogic& gameLogic, Draw& draw, FileLoader& fileLoader, Render& render,
                                        RenderBuffer& GlobalRenderBuffer, UserInput& userInput) {
    // Update game board for user input
    if (userInput.isNewInput) {
        if (userInput.leftMouseClick) {
            gameLogic.leftClick(userInput.point.x, userInput.point.y);
            userInput.isNewInput = 0;
            userInput.leftMouseClick = 0;
            // DEBUG CODE
            //draw.drawTexture(userInput.point.x, userInput.point.y, fileLoader.getTextureBMP("number_1"), GlobalRenderBuffer);
        }
        else if(userInput.rightMouseClick) {
            gameLogic.rightClick(userInput.point.x, userInput.point.y);
            userInput.isNewInput = 0;
            userInput.rightMouseClick = 0;
        }
    }
    // Render the game board
    render.updateAndDisplayBoard(gameLogic, draw, fileLoader, GlobalRenderBuffer);
}

void GameControl::startUpGame(GameLogic& gameLogic, FileLoader& fileLoader) {
    fileLoader.loadAllTextures();
    fileLoader.loadFileHelper("config", FileLoader::config);
    gameLogic.loadGameData();
}