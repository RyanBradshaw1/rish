#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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

    // select scroll from tilemapTexture
    scroll.setTexture(tilemapTexture);
    scroll.setTextureRect(sf::IntRect(2 * tileWidth, 5 * tileHeight, tileWidth, tileHeight));
    scrollColumn = 8;
    scrollRow = 8;

    // select treasure chests for items from tilemapTexture
    chestHealthPotion.setTexture(tilemapTexture);
    chestHealthPotion.setTextureRect(sf::IntRect(5 * tileWidth, 7 * tileHeight, tileWidth, tileHeight));

    chestManaPotion.setTexture(tilemapTexture);
    chestManaPotion.setTextureRect(sf::IntRect(5 * tileWidth, 7 * tileHeight, tileWidth, tileHeight));

    chestSword.setTexture(tilemapTexture);
    chestSword.setTextureRect(sf::IntRect(5 * tileWidth, 7 * tileHeight, tileWidth, tileHeight));

    chestScroll.setTexture(tilemapTexture);
    chestScroll.setTextureRect(sf::IntRect(5 * tileWidth, 7 * tileHeight, tileWidth, tileHeight));

    //set items on map
    healthPotion.setPosition(sf::Vector2f(tileWidth * healthPotionColumn, tileHeight * healthPotionRow));
    chestHealthPotion.setPosition(sf::Vector2f(tileWidth * healthPotionColumn, tileHeight * healthPotionRow));
    manaPotion.setPosition(sf::Vector2f(tileWidth * manaPotionColumn, tileHeight * manaPotionRow));
    chestManaPotion.setPosition(sf::Vector2f(tileWidth * manaPotionColumn, tileHeight * manaPotionRow));
    sword.setPosition(sf::Vector2f(tileWidth * swordColumn, tileHeight * swordRow));
    chestSword.setPosition(sf::Vector2f(tileWidth * swordColumn, tileHeight * swordRow));
    scroll.setPosition(sf::Vector2f(tileWidth * scrollColumn, tileHeight * scrollRow));
    chestScroll.setPosition(sf::Vector2f(tileWidth * scrollColumn, tileHeight * scrollRow));

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
    enemyHealth = 14;
    enemyMaxHealth = 14;
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
    titleText.setFont(font);
    titleText.setString("RISH");
    titleText.setScale(sf::Vector2f(.5, .5));
    titleText.setPosition(sf::Vector2f(195, 0));
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
                if ((event.key.code == sf::Keyboard::Space) && (heroHealth > 0) && (haveSword == true))
                {
                    // if enemy is right of hero, left of hero, above hero, below hero, or on top of
                    if ((heroTileId == enemyTileId - 1) || (heroTileId == enemyTileId + 1) || (heroTileId == enemyTileId + mapWidth) || (heroTileId == enemyTileId - mapWidth) || (heroTileId == enemyTileId))
                    {
                        enemyHealth = enemyHealth - 1;
                        enemyHealthBar.setSize(sf::Vector2f((enemyHealth / enemyMaxHealth) * 16, 2));
                    }
                }

                // magic attack key
                if ((event.key.code == sf::Keyboard::F) && (heroHealth > 0) && (heroMana > 0) && (haveScroll == true))
                {
                    // if enemy is right, left, above, below, or any four corners relative to hero or on top of
                    if ((heroTileId == enemyTileId - 1) || (heroTileId == enemyTileId + 1) || (heroTileId == enemyTileId + mapWidth) || (heroTileId == enemyTileId - mapWidth) ||
                        (heroTileId == enemyTileId + mapWidth - 1) || (heroTileId == enemyTileId + mapWidth + 1) || (heroTileId == enemyTileId - mapWidth + 1) || (heroTileId == enemyTileId - mapWidth - 1) ||
                        (heroTileId == enemyTileId))
                    {
                        enemyHealth = enemyHealth - 2;
                        heroMana = heroMana - 1;
                        heroManaBar.setSize(sf::Vector2f((heroMana / heroMaxMana) * 16, 2));
                        enemyHealthBar.setSize(sf::Vector2f((enemyHealth / enemyMaxHealth) * 16, 2));
                    }
                }

                // interact key
                if (event.key.code == sf::Keyboard::G)
                {
                    // health potion chest
                    if ((heroTileId == 32) || (heroTileId == 12) || (heroTileId == 21) || (heroTileId == 23))
                    {
                        healthPotionChest = false;
                    }
                    // mana potion chest
                    if ((heroTileId == 36) || (heroTileId == 16) || (heroTileId == 25) || (heroTileId == 27))
                    {
                        manaPotionChest = false;
                    }
                    // sword chest
                    if ((heroTileId == 71) || (heroTileId == 82))
                    {
                        swordChest = false;
                    }
                    // scroll chest
                    if ((heroTileId == 78) || (heroTileId == 87))
                    {
                        scrollChest = false;
                    }

                }


                // health potion key
                if ((event.key.code == sf::Keyboard::Q) && (heroHealth > 0) && (heroHealth < 4) && (healthPotionCount > 0))
                {
                    healthPotionCount = healthPotionCount - 1;
                    heroHealth = heroHealth + 2;
                    if (heroHealth > heroMaxHealth)
                    {
                        heroHealth = heroMaxHealth;
                    }
                    heroHealthBar.setSize(sf::Vector2f((heroHealth / heroMaxHealth) * 16, 2));
                }

                // mana potion key
                if ((event.key.code == sf::Keyboard::W) && (heroMana < 4) && (manaPotionCount > 0))
                {
                    manaPotionCount = manaPotionCount - 1;
                    heroMana = heroMana + 2;
                    if (heroMana > heroMaxMana)
                    {
                        heroMana = heroMaxMana;
                    }
                    heroManaBar.setSize(sf::Vector2f((heroMana / heroMaxMana) * 16, 2));
                }

                // movement keys
                // up
                if (event.key.code == sf::Keyboard::Up)
                {
                    didMoveUp = true;

                    // check for obstacles moving up
                    // top of map
                    if (heroPosY == 1)
                    {
                        didMoveUp = false;
                    }
                    // top right map obstacle
                    if (heroTileId == 28)
                    {
                        didMoveUp = false;
                    }
                    // health potion chest
                    if ((heroTileId == 32) && (healthPotionChest))
                    {
                        didMoveUp = false;
                    }
                    // mana potion chest
                    if ((heroTileId == 36) && (manaPotionChest))
                    {
                        didMoveUp = false;
                    }

                    // move if obstacle check passes
                    if (didMoveUp)
                    {
                        heroPosY = heroPosY - 1;
                        didMoveUp = false;
                    }
                }

                // down
                else if (event.key.code == sf::Keyboard::Down)
                {
                    didMoveDown = true;

                    // check for obstacles moving down
                    // bottom of map
                    if (heroPosY == 8)
                    {
                        didMoveDown = false;
                    }
                    // health potion chest
                    if ((heroTileId == 12) && (healthPotionChest))
                    {
                        didMoveDown = false;
                    }
                    // mana potion chest
                    if ((heroTileId == 16) && (manaPotionChest))
                    {
                        didMoveDown = false;
                    }
                    // sword chest
                    if ((heroTileId == 71) && (swordChest))
                    {
                        didMoveDown = false;
                    }
                    // scroll chest
                    if ((heroTileId == 78) && (scrollChest))
                    {
                        didMoveDown = false;
                    }

                    // move if obstacle check passes
                    if (didMoveDown)
                    {
                        heroPosY = heroPosY + 1;
                        didMoveDown = false;
                    }
                }
                // left
                else if (event.key.code == sf::Keyboard::Left)
                {
                    didMoveLeft = true;

                    // check for obstacles moving left
                    // left side of map
                    if (heroPosX == 1)
                    {
                        didMoveLeft = false;
                    }
                    // ramp obstacle
                    if ((heroTileId == 44) || (heroTileId == 34) || (heroTileId == 24) || (heroTileId == 14))
                    {
                        didMoveLeft = false;
                    }
                    // health potion chest
                    if ((heroTileId == 23) && (healthPotionChest))
                    {
                        didMoveLeft = false;
                    }
                    // mana potion chest
                    if ((heroTileId == 27) && (manaPotionChest))
                    {
                        didMoveLeft = false;
                    }
                    // sword chest
                    if ((heroTileId == 82) && (swordChest))
                    {
                        didMoveLeft = false;
                    }

                    // move if obstacle check passes
                    if (didMoveLeft)
                    {
                        heroPosX = heroPosX - 1;
                        didMoveLeft = false;
                    }
                }
                // right
                else if (event.key.code == sf::Keyboard::Right)
                {
                    didMoveRight = true;

                    // check for obstacles moving right
                    // right side of map
                    if (heroPosX == 8)
                    {
                        didMoveRight = false;
                    }
                    // ramp obstacle
                    if ((heroTileId == 43) || (heroTileId == 33) || (heroTileId == 23) || (heroTileId == 13) || (heroTileId == 17))
                    {
                        didMoveRight = false;
                    }
                    // health potion chest
                    if ((heroTileId == 21) && (healthPotionChest))
                    {
                        didMoveRight = false;
                    }
                    // mana potion chest
                    if ((heroTileId == 25) && (manaPotionChest))
                    {
                        didMoveRight = false;
                    }
                    // scroll chest
                    if ((heroTileId == 87) && (scrollChest))
                    {
                        didMoveRight = false;
                    }

                    if (didMoveRight)
                    {
                        heroPosX = heroPosX + 1;
                        didMoveRight = false;
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

    // scroll position
    int scrollPosY = scrollRow;
    int scrollPosX = scrollColumn;

    // tile ID for hero and acquirable items
    int heroTileId = heroPosX + (heroPosY * mapWidth);
    int healthPotionTileId = healthPotionPosX + (healthPotionPosY * mapWidth);
    int manaPotionTileId = manaPotionPosX + (manaPotionPosY * mapWidth);
    int swordTileId = swordPosX + (swordPosY * mapWidth);
    int scrollTileId = scrollPosX + (scrollPosY * mapWidth);

    // if hero grabs health potion
    if (healthPotionVisible)
    {
        if (heroTileId == healthPotionTileId)
        {
            healthPotionVisible = false;
            haveHealthPotion = true;
            healthPotionCount = healthPotionCount + 1;
        }
    }
    // put health potion in inventory when collected
    if (haveHealthPotion)
    {
        healthPotion.setPosition(sf::Vector2f(tileWidth * 10, tileHeight * 8));
        healthPotionInventoryText.setFont(font);
        healthPotionInventoryText.setString("[Q] Health Potion x" + std::to_string(healthPotionCount));
        healthPotionInventoryText.setScale(sf::Vector2f(.2, .2));
        healthPotionInventoryText.setPosition(sf::Vector2f(tileWidth * 11, (tileHeight * 8) + 8));
    }

    // if hero grabs mana potion
    if (manaPotionVisible)
    {
        if (heroTileId == manaPotionTileId)
        {
            manaPotionVisible = false;
            haveManaPotion = true;
            manaPotionCount = manaPotionCount + 1;
            // heroMana = heroMana + 1;
            // heroManaBar.setSize(sf::Vector2f((heroMana / heroMaxMana) * 16, 2));
        }
    }
    // put mana potion in inventory when collected
    if (haveManaPotion)
    {
        manaPotion.setPosition(sf::Vector2f(tileWidth * 10, tileHeight * 9));
        manaPotionInventoryText.setFont(font);
        manaPotionInventoryText.setString("[W] Mana Potion x" + std::to_string(manaPotionCount));
        manaPotionInventoryText.setScale(sf::Vector2f(.2, .2));
        manaPotionInventoryText.setPosition(sf::Vector2f(tileWidth * 11, (tileHeight * 9) + 8));
    }

    // if hero grabs sword
    if (swordVisible)
    {
        if (heroTileId == swordTileId)
        {
            swordVisible = false;
            haveSword = true;
        }
    }
    // put sword in hero inventory
    if (haveSword)
    {
        sword.setPosition(sf::Vector2f(tileWidth * 10, tileHeight * 1));
        swordInventoryText.setFont(font);
        swordInventoryText.setString("[Space] Melee Attack");
        swordInventoryText.setScale(sf::Vector2f(.2, .2));
        swordInventoryText.setPosition(sf::Vector2f(tileWidth * 11, (tileHeight * 1) + 8));
    }

    // if hero grabs scroll
    if (scrollVisible)
    {
        if (heroTileId == scrollTileId)
        {
            scrollVisible = false;
            haveScroll = true;
        }
    }
    // put scroll in inventory
    if (haveScroll)
    {
        scroll.setPosition(sf::Vector2f(tileWidth * 10, tileHeight * 2));
        scrollInventoryText.setFont(font);
        scrollInventoryText.setString("[F] Magic Attack");
        scrollInventoryText.setScale(sf::Vector2f(.2, .2));
        scrollInventoryText.setPosition(sf::Vector2f(tileWidth * 11, (tileHeight * 2) + 8));
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
    // clear window and set view
    _window.clear();
    _window.setView(view);

    // draw title text
    _window.draw(titleText);

    // draw map
    _window.draw(mapVerts, &tilemapTexture);

    // draw items
    // health potion & chest
    if (healthPotionChest)
    {
        _window.draw(chestHealthPotion);
    }
    else
    {
        if ((healthPotionVisible == true) || (haveHealthPotion == true))
            {
                _window.draw(healthPotion);
                _window.draw(healthPotionInventoryText);
            }
    }
    // mana potion & chest
    if (manaPotionChest)
    {
        _window.draw(chestManaPotion);
    }
    else
    {
        if ((manaPotionVisible) || (haveManaPotion))
        {
            _window.draw(manaPotion);
            _window.draw(manaPotionInventoryText);
        }
    }
    // sword & chest
    if (swordChest)
    {
        _window.draw(chestSword);
    }
    else
    {
        if ((swordVisible) || (haveSword))
        {
            _window.draw(sword);
            _window.draw(swordInventoryText);
        }
    }
    // scroll & chest
    if (scrollChest)
    {
        _window.draw(chestScroll);
    }
    else
    {
        if ((scrollVisible) || (haveScroll))
        {
            _window.draw(scroll);
            _window.draw(scrollInventoryText);
        }
    }

    // draw hero and health and mana bars if hero is alive
    if (heroHealth > 0)
    {
        _window.draw(hero);
        _window.draw(heroBackgroundBar);
        _window.draw(heroHealthBar);
        _window.draw(heroManaBar);
    }

    // draw enemy and health bar if enemy is alive
    if (enemyHealth > 0)
    {
        _window.draw(enemy);
        _window.draw(enemyBackgroundBar);
        _window.draw(enemyHealthBar);
    }

    // display drawings
    _window.display();
}
