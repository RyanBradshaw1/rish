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
        sf::Font font;
        sf::Text text;
        sf::VertexArray mapVerts;
        sf::View view;
};

#endif // GAME_H
