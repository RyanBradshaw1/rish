#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Initialize window, texture, and font
Game::Game() : _window(sf::VideoMode(1280, 720), "RISH"), hero(), enemy(), view(sf::FloatRect(0, 0, 260, 160))
{
    // Load texture and font
    if (!tilemapTexture.loadFromFile("tilemap.png"))
    {
        throw std::runtime_error("Unable to load texture");
    }
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error("Unable to load font");
    }

    // Set size of tile map
    mapHeight = 10;
    mapWidth = 10;

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
    tileWidth = 16;
    tileHeight = 16;

    // number of tiles in texture rows and columns
    numTilesAcrossTexture = tilemapTexture.getSize().x / tileWidth;
    numTilesDownTexture = tilemapTexture.getSize().y / tileHeight;

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
    // select hero from tilemapTexture
    hero.setTexture(tilemapTexture);
    hero.setTextureRect(sf::IntRect(0, 7 * tileHeight, tileWidth, tileHeight));

    // select enemy from tilemapTexture
    enemy.setTexture(tilemapTexture);
    enemy.setTextureRect(sf::IntRect(4 * tileWidth, 10 * tileHeight, tileWidth, tileHeight));

    // set hero health and position to draw hero
    heroHealth = 1;
    heroColumn = 5;
    heroRow = 5;
    hero.setPosition(sf::Vector2f(tileWidth * heroColumn, tileHeight * heroRow));

    // set enemy health and position to draw enemy
    enemyHealth = 1;
    enemyColumn = 5;
    enemyRow = 3;
    enemy.setPosition(sf::Vector2f(tileWidth * enemyColumn, tileHeight * enemyRow));

    // set font
    text.setFont(font);
    text.setString("RISH");
    text.setScale(sf::Vector2f(.5, .5));
    text.setPosition(sf::Vector2f(180, 0));
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
                // hero position
                int heroPosY = heroRow;
                int heroPosX = heroColumn;

                // enemy position
                int enemyPosY = enemyRow;
                int enemyPosX = enemyColumn;

                // tile ID for hero and enemy
                int heroTileId = heroPosX + (heroPosY * mapWidth);
                int enemyTileId = enemyPosX + (enemyPosY * mapWidth);

                // attack key
                if ((event.key.code == sf::Keyboard::Space) && (heroHealth > 0))
                {
                    if ((heroTileId == enemyTileId - 1) || (heroTileId == enemyTileId + 1) || (heroTileId == enemyTileId + mapWidth) || (heroTileId == enemyTileId - mapWidth) )
                    {
                        enemyHealth = enemyHealth - 1;
                    }
                }

                // movement keys
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (heroPosY > 1)
                    {
                        if (heroTileId != 28)
                        {
                            heroPosY = heroPosY - 1;
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (heroPosY < mapHeight - 2)
                    {
                        heroPosY = heroPosY + 1;
                    }
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (heroPosX > 1)
                    {
                        if ((heroTileId !=44) && (heroTileId !=34) && (heroTileId !=24) && (heroTileId !=14))
                        {
                        heroPosX = heroPosX - 1;
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (heroPosX < mapWidth - 2)
                    {
                        if ((heroTileId !=43) && (heroTileId !=33) && (heroTileId !=23) && (heroTileId !=13) && (heroTileId !=17))
                        {
                        heroPosX = heroPosX + 1;
                        }
                    }
                }
                // set hero's new position
                heroColumn = heroPosX;
                heroRow = heroPosY;
                hero.setPosition(sf::Vector2f(tileWidth * heroColumn, tileHeight * heroRow));

                // hero takes damage from enemy
                if ((heroColumn == enemyColumn) && (heroRow == enemyRow) && (enemyHealth > 0))
                {
                    heroHealth = heroHealth - 1;
                }
            }
        }
    }
}


// Updates game logic
void Game::update()
{
    // coordinates rat will path to
    int ratPath[] = {
        5, 3,
        6, 3,
        6, 4,
        7, 4,
        7, 5,
        7, 4,
        6, 4,
        6, 3,
    };
    // location of rat

    // sizeof(ratPath) = 16 elements * 4 byes in 32-bit integer = 64
    // ratFinalPathIndex = ((16 * 4) / (2 * 4) - 1) = 7; last index in ratPath array
    int ratFinalPathIndex = ((sizeof(ratPath) / (2 * sizeof(int))) - 1);

    // return elapsed time and convert to seconds
    float dt = clock.restart().asSeconds();

    // add elapsed time to rat's "turn meter"
    ratTurn = ratTurn + dt;
    // determine if rat should move based on if enough time has passed
    if (ratTurn >= ratTurnMeter)
    {
        ratTurn = ratTurn - ratTurnMeter;
        //shouldRatMove = true;
        int nextRatColumn = ratPath[ratCurrentPathIndex * 2];
        int ratColumn = nextRatColumn;
        int nextRatRow = ratPath[ratCurrentPathIndex * 2 + 1];
        int ratRow = nextRatRow;
        enemy.setPosition(sf::Vector2f(tileWidth * ratColumn, tileHeight * ratRow));
        ratCurrentPathIndex = ratCurrentPathIndex + 1;

        // reduce hero health if rat paths into hero
        if ((ratColumn == heroColumn) && (ratRow == heroRow) && (enemyHealth > 0))
        {
            heroHealth = heroHealth - 1;
        }

        // reset path index for rat
        if (ratCurrentPathIndex > ratFinalPathIndex)
        {
            ratCurrentPathIndex = 0;
        }
    }
}

// Render game to screen
void Game::render()
{
    _window.clear();
    _window.setView(view);
    _window.draw(text);
    _window.draw(mapVerts, &tilemapTexture);
    if (heroHealth > 0)
    {
        _window.draw(hero);
    }
    if (enemyHealth > 0)
    {
    _window.draw(enemy);
    }
    _window.display();
}
