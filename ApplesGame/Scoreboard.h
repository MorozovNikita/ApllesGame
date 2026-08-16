#pragma once

#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    class Scoreboard
    {
    public:
        void init();
        void update(int numEatenApples);
        void draw(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text scoreText;
    };

} // namespace ApplesGame