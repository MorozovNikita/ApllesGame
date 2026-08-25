#include "LeaderboardScreen.h"

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    LeaderboardScreen::LeaderboardScreen(LeaderboardBase& leaderBoard, const sf::Font& font)
        : m_leaderboard(leaderBoard)
        , m_font(font)
    {
        init();
    }

    void LeaderboardScreen::init()
    {
        m_titleText = createText(m_font, LD_TITLE_SIZE, titleColor);
        m_titleText.setString("HIGH SCORES");
        centerTextHorizontally(m_titleText, SCREEN_WIDTH / 2.f, LD_TITLE_Y);

        m_hintText = createText(m_font, LD_HINT_SIZE, hintColor);
        m_hintText.setString("ESC or ENTER - back to menu");
        centerTextHorizontally(m_hintText, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - LD_HINT_Y_OFFSET);
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

                if (event.type == sf::Event::KeyPressed 
                    && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter))
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

        const auto& records = m_leaderboard.getRecords();

        if (records.empty())
        {
            sf::Text empty = createText(m_font, LD_EMPTY_SIZE, hintColor);
            empty.setString("Leaderboard is empty"s);
            centerTextHorizontally(empty, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            window.draw(empty);
        }
        else
        {
            int i{ 0 };
            for (const Record& record : records)
            {
                const auto& entry = records;
                const float y = LD_START_Y + i++ * LD_ROW_SPACING;
                const std::string rankStr = std::to_string(i) + ".";

                sf::Text rank = createText(m_font, LD_ENTRY_SIZE, textColor);
                rank.setString(rankStr);
                rank.setPosition(LD_RANK_X, y);
                window.draw(rank);

                sf::Text name = createText(m_font, LD_ENTRY_SIZE, textColor);
                name.setString(record.name);
                name.setPosition(LD_NAME_X, y);
                window.draw(name);

                sf::Text score = createText(m_font, LD_ENTRY_SIZE, textColor);
                score.setString(std::to_string(record.score));
                score.setPosition(LD_SCORE_X, y);
                window.draw(score);
            }
        }

        window.draw(m_hintText);
        window.display();
    }

    sf::Text LeaderboardScreen::createText(const sf::Font& font, int size, sf::Color color)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        return text;
    }
}