#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update();
        void render();
        // game window
        sf::RenderWindow _window;
        // tilemap with several sprites on it
        sf::Texture tilemapTexture;
        // verts for drawing map
        sf::VertexArray mapVerts;
        // view area
        sf::View view;
        // Sprites
        sf::Sprite hero;
        sf::Sprite rat;
        sf::Sprite healthPotion;
        sf::Sprite manaPotion;
        sf::Sprite sword;
        sf::Sprite scroll;
        sf::Sprite chestHealthPotion;
        sf::Sprite chestManaPotion;
        sf::Sprite chestSword;
        sf::Sprite chestScroll;
        // font and texts
        sf::Font font;
        sf::Text titleText;
        sf::Text swordInventoryText;
        sf::Text scrollInventoryText;
        sf::Text healthPotionInventoryText;
        sf::Text manaPotionInventoryText;
        // sprite locations
        sf::Int8 heroColumn;
        sf::Int8 heroRow;
        sf::Int8 ratColumn;
        sf::Int8 ratRow;
        bool isRatAlive = true;
        sf::Int8 healthPotionColumn;
        sf::Int8 healthPotionRow;
        sf::Int8 manaPotionRow;
        sf::Int8 manaPotionColumn;
        sf::Int8 swordRow;
        sf::Int8 swordColumn;
        sf::Int8 scrollRow;
        sf::Int8 scrollColumn;
        // is each item in a chest or visible
        bool healthPotionVisible = true;
        bool healthPotionChest = true;
        bool manaPotionVisible = true;
        bool manaPotionChest = true;
        bool swordVisible = true;
        bool swordChest = true;
        bool scrollVisible = true;
        bool scrollChest = true;
        // inventory
        bool haveSword = false;
        bool haveScroll = false;
        bool haveHealthPotion = false;
        bool haveManaPotion = false;
        // inventory count
        sf::Int8 healthPotionCount = 0;
        sf::Int8 manaPotionCount = 0;
        // movement checks
        bool didMoveUp = false;
        bool didMoveDown = false;
        bool didMoveLeft = false;
        bool didMoveRight = false;
        // tilemap variables
        sf::Int8 mapHeight;
        sf::Int8 mapWidth;
        sf::Int8 tileHeight;
        sf::Int8 tileWidth;
        sf::Int8 numTilesAcrossTexture;
        sf::Int8 numTilesDownTexture;
        // health and mana values
        float heroHealth;
        float heroMaxHealth;
        float heroMana;
        float heroMaxMana;
        float ratHealth;
        float ratMaxHealth;
        // for tracking time
        sf::Clock clock;
        sf::Time deltaTime;
        sf::Time elapsed;
        // determine if it's time for enemy to move
        float ratTurn = 0.0f;
        float ratTurnMeter = 1.0f;
        sf::Int8 ratCurrentPathIndex = 0;
        // visual representation of health and mana
        sf::RectangleShape heroHealthBar;
        sf::RectangleShape heroManaBar;
        sf::RectangleShape heroBackgroundBar;
        sf::RectangleShape ratHealthBar;
        sf::RectangleShape ratBackgroundBar;
};

#endif // GAME_H
