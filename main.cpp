
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RISH");


    sf::Texture tilemapTexture;
    tilemapTexture.loadFromFile("tilemap.png");
    sf::Sprite tilemap(tilemapTexture);
    tilemap.setScale(sf::Vector2f(3.8, 3.8));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(tilemap);

        window.display();
    }
}
