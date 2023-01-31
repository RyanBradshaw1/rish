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
        sf::Sprite hero;
        sf::Sprite enemy;
        sf::Font font;
        sf::Text text;
        sf::VertexArray mapVerts;
        sf::View view;
        sf::Int16 heroColumn;
        sf::Int16 heroRow;
        sf::Int16 enemyColumn;
        sf::Int16 enemyRow;
        sf::Int16 mapHeight;
        sf::Int16 mapWidth;
        sf::Int16 tileHeight;
        sf::Int16 tileWidth;
        sf::Int16 numTilesAcrossTexture;
        sf::Int16 numTilesDownTexture;
        sf::Int16 heroHealth;
};

#endif // GAME_H
