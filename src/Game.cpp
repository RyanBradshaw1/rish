#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Initialize window, texture, and font
Game::Game() : _window(sf::VideoMode(1280, 720), "RISH"), view(sf::FloatRect(0, 0, 260, 160))
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
        // map tile IDs
        40, 40, 40, 40, 40, 40, 40, 40, 20, 40,
        40, 12, 0, 13, 53, 48, 49, 52, 32, 40,
        40, 0, 0, 13, 48, 48, 48, 48, 51, 40,
        40, 12, 0, 13, 49, 48, 48, 48, 48, 40,
        40, 36, 37, 38, 48, 48, 48, 49, 48, 40,
        40, 50, 51, 52, 48, 48, 48, 48, 48, 40,
        40, 48, 48, 48, 48, 48, 42, 48, 48, 40,
        40, 48, 48, 48, 48, 48, 48, 48, 49, 40,
        40, 49, 48, 48, 49, 48, 48, 48, 48, 40,
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
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

    // select health potion from tilemapTexture
    healthPotion.setTexture(tilemapTexture);
    healthPotion.setTextureRect(sf::IntRect(6 * tileWidth, 9 * tileHeight, tileWidth, tileHeight));
    healthPotionColumn = 2;
    healthPotionRow = 2;

    // select mana potion from tilemapTexture
    manaPotion.setTexture(tilemapTexture);
    manaPotion.setTextureRect(sf::IntRect(8 * tileWidth, 9 * tileHeight, tileWidth, tileHeight));
    manaPotionColumn = 6;
    manaPotionRow = 2;

    // select sword from tilemapTexture
    sword.setTexture(tilemapTexture);
    sword.setTextureRect(sf::IntRect(8 * tileWidth, 8 * tileHeight, tileWidth, tileHeight));
    swordColumn = 1;
    swordRow = 8;

    //set items on map
    healthPotion.setPosition(sf::Vector2f(tileWidth * healthPotionColumn, tileHeight * healthPotionRow));
    manaPotion.setPosition(sf::Vector2f(tileWidth * manaPotionColumn, tileHeight * manaPotionRow));
    sword.setPosition(sf::Vector2f(tileWidth * swordColumn, tileHeight * swordRow));

    // set hero health, mana, and position to draw hero
    heroHealth = 4;
    heroMaxHealth = 4;
    heroMana = 4;
    heroMaxMana = 4;
    heroColumn = 5;
    heroRow = 5;
    hero.setPosition(sf::Vector2f(tileWidth * heroColumn, tileHeight * heroRow));

    // set hero max health bar for background
    heroBackgroundBar.setSize(sf::Vector2f(16, 4));
    heroBackgroundBar.setPosition(hero.getPosition() + sf::Vector2f(0, -5));
    heroBackgroundBar.setFillColor(sf::Color{0, 0, 0, 50});

    // set hero's current health bar
    heroHealthBar.setSize(sf::Vector2f((heroHealth / heroMaxHealth) * 16, 2));
    heroHealthBar.setPosition(hero.getPosition() + sf::Vector2f(0, -5));
    heroHealthBar.setFillColor(sf::Color{0, 255, 0, 255});

    // set hero mana bar
    heroManaBar.setSize(sf::Vector2f(16, 2));
    heroManaBar.setPosition(hero.getPosition() + sf::Vector2f(0, -3));
    heroManaBar.setFillColor(sf::Color{0, 0, 255, 255});

    // set enemy health and position to draw enemy
    enemyHealth = 12;
    enemyMaxHealth = 12;
    enemyColumn = 5;
    enemyRow = 3;
    enemy.setPosition(sf::Vector2f(tileWidth * enemyColumn, tileHeight * enemyRow));

    // set enemy max health bar for background
    enemyBackgroundBar.setSize(sf::Vector2f(16, 2));
    enemyBackgroundBar.setPosition(enemy.getPosition() + sf::Vector2f(0, -5));
    enemyBackgroundBar.setFillColor(sf::Color{0, 0, 0, 50});

    // set enemy's current health bar
    enemyHealthBar.setSize(sf::Vector2f((enemyHealth / enemyMaxHealth) * 16, 2));
    enemyHealthBar.setPosition(enemy.getPosition() + sf::Vector2f(0, -5));
    enemyHealthBar.setFillColor(sf::Color{0, 255, 0, 255});

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
                if ((event.key.code == sf::Keyboard::Space) && (heroHealth > 0) && (swordVisible == false))
                {
                    // if enemy is right of hero, left of hero, above hero, or below hero
                    if ((heroTileId == enemyTileId - 1) || (heroTileId == enemyTileId + 1) || (heroTileId == enemyTileId + mapWidth) || (heroTileId == enemyTileId - mapWidth) )
                    {
                        enemyHealth = enemyHealth - 1;
                        enemyHealthBar.setSize(sf::Vector2f((enemyHealth / enemyMaxHealth) * 16, 2));
                    }
                }

                // magic attack key
                if ((event.key.code == sf::Keyboard::F) && (heroHealth > 0) && (heroMana > 0))
                {
                    // if enemy is right, left, above, below, or any four corners relative to hero
                    if ((heroTileId == enemyTileId - 1) || (heroTileId == enemyTileId + 1) || (heroTileId == enemyTileId + mapWidth) || (heroTileId == enemyTileId - mapWidth) ||
                        (heroTileId == enemyTileId + mapWidth - 1) || (heroTileId == enemyTileId + mapWidth + 1) || (heroTileId == enemyTileId - mapWidth + 1) || (heroTileId == enemyTileId - mapWidth - 1))
                    {
                        enemyHealth = enemyHealth - 2;
                        heroMana = heroMana - 1;
                        heroManaBar.setSize(sf::Vector2f((heroMana / heroMaxMana) * 16, 2));
                        enemyHealthBar.setSize(sf::Vector2f((enemyHealth / enemyMaxHealth) * 16, 2));
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
                // set new position for hero and health bar
                heroColumn = heroPosX;
                heroRow = heroPosY;
                hero.setPosition(sf::Vector2f(tileWidth * heroPosX, tileHeight * heroPosY));
                heroBackgroundBar.setPosition(hero.getPosition() + sf::Vector2f(0, -5));
                heroHealthBar.setPosition(hero.getPosition() + sf::Vector2f(0, -5));
                heroManaBar.setPosition(hero.getPosition() + sf::Vector2f(0, -3));

                // hero takes damage when moving over an enemy
                if ((heroColumn == enemyColumn) && (heroRow == enemyRow) && (enemyHealth > 0) && (ratCurrentPathIndex = 2))
                {
                    heroHealth = heroHealth - 1;
                    heroHealthBar.setSize(sf::Vector2f((heroHealth / heroMaxHealth) * 16, 2));
                }
            }
        }
    }
}


// Updates game logic
void Game::update()
{
    // hero position
    int heroPosY = heroRow;
    int heroPosX = heroColumn;

    // health potion position
    int healthPotionPosY = healthPotionRow;
    int healthPotionPosX = healthPotionColumn;

    // mana potion position
    int manaPotionPosY = manaPotionRow;
    int manaPotionPosX = manaPotionColumn;

    // sword position
    int swordPosY = swordRow;
    int swordPosX = swordColumn;

    // tile ID for hero and acquirable items
    int heroTileId = heroPosX + (heroPosY * mapWidth);
    int healthPotionTileId = healthPotionPosX + (healthPotionPosY * mapWidth);
    int manaPotionTileId = manaPotionPosX + (manaPotionPosY * mapWidth);
    int swordTileId = swordPosX + (swordPosY * mapWidth);

    // if hero grabs health potion
    if (healthPotionVisible)
    {
        if ((heroTileId == healthPotionTileId) && (heroHealth < heroMaxHealth))
        {
            healthPotionVisible = false;
            heroHealth = heroHealth + 1;
            heroHealthBar.setSize(sf::Vector2f((heroHealth / heroMaxHealth) * 16, 2));
        }
    }

    // if hero grabs mana potion
    if (manaPotionVisible)
    {
        if ((heroTileId == manaPotionTileId) && (heroMana < heroMaxMana))
        {
            manaPotionVisible = false;
            heroMana = heroMana + 1;
            heroManaBar.setSize(sf::Vector2f((heroMana / heroMaxMana) * 16, 2));
        }
    }

    // if her grabs sword
    if (swordVisible)
    {
        if (heroTileId == swordTileId)
        {
            swordVisible = false;
        }
    }

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

    // sizeof(ratPath) = 16 elements * 4 byes in 32-bit integer = 64
    // ratFinalPathIndex = ((16 * 4) / (2 * 4) - 1) = 7; last index in ratPath array
    int ratFinalPathIndex = ((sizeof(ratPath) / (2 * sizeof(int))) - 1);

    // return elapsed time and convert to seconds
    float dt = clock.restart().asSeconds();

    // add elapsed time to rat's turn
    ratTurn = ratTurn + dt;
    // determine if rat should move based on if enough time has passed
    if (ratTurn >= ratTurnMeter)
    {
        ratTurn = ratTurn - ratTurnMeter;
        int nextRatColumn = ratPath[ratCurrentPathIndex * 2];
        int ratColumn = nextRatColumn;
        int nextRatRow = ratPath[ratCurrentPathIndex * 2 + 1];
        int ratRow = nextRatRow;
        enemyColumn = ratColumn;
        enemyRow = ratRow;
        enemy.setPosition(sf::Vector2f(tileWidth * ratColumn, tileHeight * ratRow));
        enemyBackgroundBar.setPosition(sf::Vector2f(tileWidth * ratColumn, tileHeight * ratRow - 5));
        enemyHealthBar.setPosition(sf::Vector2f(tileWidth * ratColumn, tileHeight * ratRow - 5));
        ratCurrentPathIndex = ratCurrentPathIndex + 1;

        // reduce hero health if rat paths into hero
        if ((ratColumn == heroColumn) && (ratRow == heroRow) && (enemyHealth > 0))
        {
            heroHealth = heroHealth - 1;
            heroHealthBar.setSize(sf::Vector2f((heroHealth / heroMaxHealth) * 16, 2));
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

    if (swordVisible == true)
    {
        _window.draw(sword);
    }
    if (healthPotionVisible == true)
    {
        _window.draw(healthPotion);
    }

    if (manaPotionVisible == true)
    {
        _window.draw(manaPotion);
    }

    if (heroHealth > 0)
    {
        _window.draw(hero);
        _window.draw(heroBackgroundBar);
        _window.draw(heroHealthBar);
        _window.draw(heroManaBar);
    }

    if (enemyHealth > 0)
    {
        _window.draw(enemy);
        _window.draw(enemyBackgroundBar);
        _window.draw(enemyHealthBar);
    }
    _window.display();
}
