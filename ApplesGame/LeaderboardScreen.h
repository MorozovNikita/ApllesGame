#pragma once

#include <SFML/Graphics.hpp>

#include "Leaderboard.h"

namespace ApplesGame
{
    class LeaderboardScreen
    {
    public:
        void init(const sf::Font& font);
        void run(sf::RenderWindow& window);

    private:
        void draw(sf::RenderWindow& window);

        const sf::Font* m_font{ nullptr };
        Leaderboard m_leaderboard;

        sf::Text m_titleText;
        sf::Text m_hintText;
    };
}