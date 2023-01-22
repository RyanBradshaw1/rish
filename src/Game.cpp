#include "Game.h"

// Initialize window and player
Game::Game() : _window(sf::VideoMode(1280, 720), "RISH"), _player(150), _player2()
{
    _player.setFillColor(sf::Color::Blue);
    _player.setPosition(100, 20);
    _player2.setFillColor(sf::Color::Red);
    _player2.setSize(sf::Vector2f(100, 50));
    _player2.setPosition(sf::Vector2f(5, 400));
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

// Handle user input
void Game::processEvents()
{
    sf::Event event;
    while(_window.pollEvent(event))
    {
        if ((event.type == sf::Event::Closed)
        or ((event.type == sf::Event::KeyPressed) and (event.key.code == sf::Keyboard::Escape)))
        {
            _window.close();
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
    _window.draw(_player);
    _window.draw(_player2);
    _window.display();
}
