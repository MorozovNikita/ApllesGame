#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "GlobalLeaderboard.h"

namespace ApplesGame
{
    class LeaderboardScreen
    {
    public:
        LeaderboardScreen(LeaderboardBase& leaderboard, const sf::Font& font);
        ~LeaderboardScreen() = default;

        void run(sf::RenderWindow& window);

    private:
        const sf::Font& m_font;
        LeaderboardBase& m_leaderboard;

        sf::Text m_titleText;
        sf::Text m_hintText;

        void init();
        void draw(sf::RenderWindow& window);

        sf::Text createText(const sf::Font& font, int size, sf::Color color);
    };
}