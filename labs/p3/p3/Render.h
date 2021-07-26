#include <SFML/Graphics.hpp>

class Render {

    void displayNumOfMines();

    public:
    void updateAndDisplayBoard(TileInfo tileInfo[],
                               sf::RenderWindow& window, 
                               TextureSpriteManager& textureSpriteManager);
};