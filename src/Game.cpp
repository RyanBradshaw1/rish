#include "Game.h"
#include <SFML/Graphics.hpp>

// Initialize window, texture, and font
Game::Game() : _window(sf::VideoMode(1280, 720), "RISH"), tilemap()
{
    if (!tilemapTexture.loadFromFile("tilemap.png"))
    {
        throw std::runtime_error("Unable to load texture");
    }
    tilemap.setTexture(tilemapTexture);
    tilemap.setPosition(sf::Vector2f(0, 0));
    tilemap.setScale(sf::Vector2f(2.5, 2.5));

    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error("Unable to load font");
    }
    text.setFont(font);
    text.setString("RISH");
    text.setPosition(sf::Vector2f(555, 0));
}

// Hides main game loop
void Game::run()
{
    while (_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

//Handle user input
void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _window.close();
            }
            else
            {
                float changeX = 0.0f;
                float changeY = 0.0f;

                if (event.key.code == sf::Keyboard::Up)
                {
                    changeY = -5.0f;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    changeY = 5.0f;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    changeX = -5.0f;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    changeX = 5.0f;
                }

                tilemap.move(sf::Vector2f(changeX, changeY));
            }
        }
    }
}


// Updates game logic
void Game::update()
{

}

// Render game to screen
void Game::render()
{
    _window.clear();
    _window.draw(tilemap);
    _window.draw(text);
    _window.display();
}
