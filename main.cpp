
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RISH");

    sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(640,360);
    rectangle.setOrigin(rectangle.getSize().x / 2,
                        rectangle.getSize().y / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Draw here
        window.draw(rectangle);

        window.display();
    }
}
