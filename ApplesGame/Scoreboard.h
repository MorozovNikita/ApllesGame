#pragma once

#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    class Scoreboard
    {
    public:
        void init(const int& totalApples);
        void update(int numEatenApples);
        void update(const int& numEatenApples, const int& totalApples);
        void draw(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text scoreText;
    };

} // namespace ApplesGame