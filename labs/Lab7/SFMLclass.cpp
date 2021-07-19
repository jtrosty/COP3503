#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                // the mouse was pressed, but which button
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // 
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    cout << "X: " << position.x << " Y " << position.y << endl;
                }
            }
        }

        window.clear();

        //add sprite. 

        sf::Vector21i mousePosition = sf::Mouse::getPosition(window);
        sprite.setPosition(mousePosition.x, mousePosition.y);
        window.draw(sprite);
        window.draw(shape);
        window.display();
    }

    TextureMangaer::LoadTexture(string fileName) {
        string path = "images/";
        path += fileName + ".png";
        textures[fileName].loadFromFile(path);
    }

    return 0;
}