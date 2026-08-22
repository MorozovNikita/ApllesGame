#include "LeaderboardScreen.h"

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    void LeaderboardScreen::init(const sf::Font& font)
    {
        m_font = &font;

        m_titleText.setFont(*m_font);
        m_titleText.setCharacterSize(28);
        m_titleText.setFillColor(titleColor);
        m_titleText.setString("HIGH SCORES");
        centerTextHorizontally(m_titleText, SCREEN_WIDTH / 2.f, 60.f);

        m_hintText.setFont(*m_font);
        m_hintText.setCharacterSize(14);
        m_hintText.setFillColor(hintColor);
        m_hintText.setString("ESC or ENTER - back to menu");
        centerTextHorizontally(m_hintText, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);

        m_leaderboard.generate(9);
    }

    void LeaderboardScreen::run(sf::RenderWindow& window)
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return;
                }

                if (event.type == sf::Event::KeyPressed &&
                    (event.key.code == sf::Keyboard::Escape ||
                        event.key.code == sf::Keyboard::Enter))
                {
                    return;
                }
            }

            draw(window);
        }
    }

    void LeaderboardScreen::draw(sf::RenderWindow& window)
    {
        window.clear(backgroundColor);

        window.draw(m_titleText);

        const auto& entries = m_leaderboard.getRecords();
        const float startY = 140.f;
        const float rowSpacing = 40.f;

        for (size_t i = 0; i < entries.size(); ++i)
        {
            const auto& entry = entries[i];
            const float y = startY + i * rowSpacing;

            sf::Text rank(std::to_string(i + 1) + ".", *m_font, 18);
            rank.setFillColor(textColor);
            rank.setPosition(100.f, y);
            window.draw(rank);

            sf::Text name(entry.name, *m_font, 18);
            name.setFillColor(textColor);
            name.setPosition(200.f, y);
            window.draw(name);

            sf::Text score(std::to_string(entry.score), *m_font, 18);
            score.setFillColor(textColor);
            score.setPosition(500.f, y);
            window.draw(score);
        }

        if (entries.empty())
        {
            sf::Text empty("Leaderboard is empty", *m_font, 20);
            empty.setFillColor(hintColor);
            centerTextHorizontally(empty, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            window.draw(empty);
        }

        window.draw(m_hintText);
        window.display();
    }
}