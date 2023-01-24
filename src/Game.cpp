#include "Game.h"
#include <SFML/Graphics.hpp>

// Initialize window, texture, and font
Game::Game() : _window(sf::VideoMode(1280, 720), "RISH"), tilemap(), view(sf::FloatRect(0, 0, 220, 180))
{
    // Load texture and set sprite
    if (!tilemapTexture.loadFromFile("tilemap.png"))
    {
        throw std::runtime_error("Unable to load texture");
    }
    tilemap.setTexture(tilemapTexture);
    //tilemap.setPosition(sf::Vector2f(0, 400));
    //tilemap.setScale(sf::Vector2f(2.5, 2.5));


    // Load and set font
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error("Unable to load font");
    }
    text.setFont(font);
    text.setString("RISH");
    text.setScale(sf::Vector2f(.5, .5));
    text.setPosition(sf::Vector2f(180, 0));

    // Set size of tile map
    int mapHeight = 10;
    int mapWidth = 10;

    // Array to represent tile map
    int map[] =
    {
        40, 40, 40, 40, 40, 40, 40, 40, 20, 40,
        40, 12, 0, 13, 53, 48, 49, 52, 32, 40,
        40, 0, 0, 13, 48, 48, 48, 48, 51, 40,
        40, 12, 0, 13, 49, 48, 48, 48, 48, 40,
        40, 36, 37, 38, 48, 48, 48, 49, 48, 40,
        40, 50, 51, 52, 48, 48, 48, 48, 48, 40,
        40, 48, 48, 48, 48, 48, 42, 48, 48, 40,
        40, 48, 48, 48, 48, 48, 48, 48, 49, 40,
        40, 49, 48, 48, 49, 48, 48, 48, 48, 40,
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40
    };

    // size of each tile
    int tileWidth = 16;
    int tileHeight = 16;

    // number of tiles in texture rows and columns
    int numTilesAcrossTexture = tilemapTexture.getSize().x / tileWidth;
    int numTilesDownTexture = tilemapTexture.getSize().y / tileHeight;

    // four vertices per tile
    mapVerts.setPrimitiveType(sf::PrimitiveType::Quads);
    mapVerts.resize(4 * mapWidth * mapHeight);

    // loop over every tile in tile map
    for (int index = 0; index < mapWidth * mapHeight; index++)
    {
        // find column and row
        int x = index % mapWidth;
        int y = index / mapWidth;
        // get tile id at index location in tile map
        int tileId = map[index];
        // find correct tile column and row
        int tileU = tileId % numTilesAcrossTexture;
        int tileV = tileId / numTilesDownTexture;
        // get pointer to current quad
        sf::Vertex *quad = &mapVerts[4 * (x + (y * mapWidth))];
        // set position for each vertex
        float left = x * tileWidth;
        float top = y * tileHeight;
        float right = (x + 1) * tileWidth;
        float bottom = (y + 1) * tileHeight;
        quad[0].position = sf::Vector2f(left, top);
        quad[1].position = sf::Vector2f(right, top);
        quad[2].position = sf::Vector2f(right, bottom);
        quad[3].position = sf::Vector2f(left, bottom);
        // set texture coordinates for each vertex
        float leftU = tileU * tileWidth;
        float topV = tileV * tileHeight;
        float rightU = (tileU + 1) * tileWidth;
        float bottomV = (tileV + 1) * tileHeight;
        quad[0].texCoords = sf::Vector2f(leftU, topV);
        quad[1].texCoords = sf::Vector2f(rightU, topV);
        quad[2].texCoords = sf::Vector2f(rightU, bottomV);
        quad[3].texCoords = sf::Vector2f(leftU, bottomV);
    }
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
    //_window.draw(tilemap);
    _window.setView(view);
    _window.draw(text);
    _window.draw(mapVerts, &tilemapTexture);
    _window.display();
}