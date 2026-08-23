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

        void setLeaderBoard(Leaderboard& leaderBoard);

    private:
        void draw(sf::RenderWindow& window);

        sf::Text createText(const sf::Font& font, int size, sf::Color color);

        const sf::Font* m_font{ nullptr };
        Leaderboard* m_leaderboard;

        sf::Text m_titleText;
        sf::Text m_hintText;
    };
}