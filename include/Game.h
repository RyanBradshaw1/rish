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

        sf::RenderWindow _window;
        sf::Texture tilemapTexture;
        // Sprites
        sf::Sprite hero;
        sf::Sprite enemy;
        sf::Sprite healthPotion;
        sf::Sprite manaPotion;
        sf::Sprite sword;
        sf::Sprite scroll;
        // font and texts
        sf::Font font;
        sf::Text titleText;
        sf::Text swordText;
        sf::Text scrollText;
        sf::Text healthPotionInventoryText;
        sf::Text manaPotionInventoryText;

        sf::VertexArray mapVerts;
        sf::View view;
        // sprite locations
        sf::Int8 heroColumn;
        sf::Int8 heroRow;
        sf::Int8 enemyColumn;
        sf::Int8 enemyRow;
        sf::Int8 healthPotionColumn;
        sf::Int8 healthPotionRow;
        bool healthPotionVisible = true;
        sf::Int8 manaPotionRow;
        sf::Int8 manaPotionColumn;
        bool manaPotionVisible = true;
        sf::Int8 swordRow;
        sf::Int8 swordColumn;
        bool swordVisible = true;
        sf::Int8 scrollRow;
        sf::Int8 scrollColumn;
        bool scrollVisible = true;
        // inventory
        bool haveSword = false;
        bool haveScroll = false;
        bool haveHealthPotion = false;
        sf::Int8 healthPotionCount = 0;
        bool haveManaPotion = false;
        sf::Int8 manaPotionCount = 0;

        sf::Int8 mapHeight;
        sf::Int8 mapWidth;
        sf::Int8 tileHeight;
        sf::Int8 tileWidth;
        sf::Int8 numTilesAcrossTexture;
        sf::Int8 numTilesDownTexture;
        float heroHealth;
        float heroMaxHealth;
        float heroMana;
        float heroMaxMana;
        float enemyHealth;
        float enemyMaxHealth;
        sf::Clock clock;
        sf::Time deltaTime;
        sf::Time elapsed;
        float ratTurn = 0.0f;
        float ratTurnMeter = 1.0f;
        sf::Int8 ratCurrentPathIndex = 0;
        sf::RectangleShape heroHealthBar;
        sf::RectangleShape heroManaBar;
        sf::RectangleShape heroBackgroundBar;
        sf::RectangleShape enemyHealthBar;
        sf::RectangleShape enemyBackgroundBar;
};

#endif // GAME_H
