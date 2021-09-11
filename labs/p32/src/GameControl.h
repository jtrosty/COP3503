#include "utils.h"

#include "GameLogic.h"
#include "Render.h"
#include "FileLoader.h"
#include "Draw.h"

class GameControl {
    private:

    public:
    void updateWindowAndUserInput(GameLogic& gameLogic, Draw& draw, FileLoader& fileLoader, Render& render, 
                                    RenderBuffer& GlobalRenderBuffer, UserInput& userInput);
    void startUpGame(GameLogic& gameLogic, FileLoader& fileLoader);

};