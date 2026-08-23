#pragma once

#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    class Scoreboard
    {
    public:
        Scoreboard(const sf::Font& font);
        ~Scoreboard() = default;

        void reset(const int& totalApples);
        void update(const int& numEatenApples);
        void update(const int& numEatenApples, const int& totalApples);
        void draw(sf::RenderWindow& window);

    private:
        sf::Text m_scoreText;
    };

} // namespace ApplesGame