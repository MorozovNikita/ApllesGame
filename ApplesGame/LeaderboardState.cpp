#include "LeaderboardState.h"

#include "GameResources.h"
#include "StateStack.h"
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    LeaderboardState::LeaderboardState(StateStack& stack, Context context)
        : State(stack, context)
        , m_font(context.resources.m_font)
        , m_leaderboard(context.leaderboard)
    {
        init();
    }

    void LeaderboardState::init()
    {
        m_titleText = createText(m_font, LD_TITLE_SIZE, TITLE_COLOR);
        m_titleText.setString("HIGH SCORES");
        centerTextHorizontally(m_titleText, SCREEN_WIDTH / 2.f, LD_TITLE_Y);

        m_hintText = createText(m_font, LD_HINT_SIZE, HINT_COLOR);
        m_hintText.setString("BACKSPACE/ESCAPE - back to menu");
        centerTextHorizontally(m_hintText, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - LD_HINT_Y_OFFSET);
    }

    void LeaderboardState::draw()
    {
        mContext.window.clear(BACKGROUND_COLOR);

        mContext.window.draw(m_titleText);

        const auto& records = m_leaderboard.getRecords();

        if (records.empty())
        {
            sf::Text empty = createText(m_font, LD_EMPTY_SIZE, HINT_COLOR);
            empty.setString("Leaderboard is empty"s);
            centerTextHorizontally(empty, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            mContext.window.draw(empty);
        }
        else
        {
            int i{ 0 };
            for (const Record& record : records)
            {
                const float y = LD_START_Y + i++ * LD_ROW_SPACING;
                const std::string rankStr = std::to_string(i) + ".";

                sf::Text rank = createText(m_font, LD_ENTRY_SIZE, TEXT_COLOR);
                rank.setString(rankStr);
                rank.setPosition(LD_RANK_X, y);
                mContext.window.draw(rank);

                sf::Text name = createText(m_font, LD_ENTRY_SIZE, TEXT_COLOR);
                name.setString(record.name);
                name.setPosition(LD_NAME_X, y);
                mContext.window.draw(name);

                sf::Text score = createText(m_font, LD_ENTRY_SIZE, TEXT_COLOR);
                score.setString(std::to_string(record.score));
                score.setPosition(LD_SCORE_X, y);
                mContext.window.draw(score);
            }
        }

        mContext.window.draw(m_hintText);

    }

    bool LeaderboardState::update(sf::Time dt)
    {
        return false;
    }

    bool LeaderboardState::handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Escape)
            {
                mStack.popState();

                if (mContext.data.showGameOver)
                {
                    mStack.pushState(States::GameOver);
                }
            }

            return false;
        }

        return true;
    }

    sf::Text LeaderboardState::createText(const sf::Font& font, int size, sf::Color color)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        return text;
    }

} // namespace ApplesGame