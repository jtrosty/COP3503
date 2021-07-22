#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureSpriteManager.h"
#include "LoadConfig.h"


using std::cout;
using std::endl;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Jon Trost RuleZ");
    sf::Sprite sprite; 

    // the cirlce
    // TODO (Jon)
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //Load textures
    TextureSpriteManager textureSpriteManager;
    textureSpriteManager.LoadAllTextures();


    //Config file
    FileLoading fileLoader;
    fileLoader.loadFileHelper("config", fileLoader.config);
    //cout << fileLoader.configData.column << endl;
    //cout << fileLoader.configData.rows << endl;
    //cout << fileLoader.configData.numOfMines << endl;


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
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(sprite);
        window.draw(textureSpriteManager.GetSprite("test_3"));
        window.display();
    }

    return 0;
}