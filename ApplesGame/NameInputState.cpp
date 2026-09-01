#include "NameInputState.h"

#include "GameResources.h"
#include "StateStack.h"
#include "Constants.h"
#include "LeaderboardBase.h"
#include "Math.h"

namespace ApplesGame
{
    NameInputState::NameInputState(StateStack& stack, Context& context)
        : State(stack, context)
        , m_font(context.resources.m_font)
    {
        m_playerName.clear();
        init();
    }

    void NameInputState::init()
    {
        const float centerX = SCREEN_WIDTH / 2.f;

        // header
        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(NAME_INPUT_TITLE_SIZE);
        m_titleText.setFillColor(TITLE_COLOR);
        m_titleText.setString("GAME OVER"s);
        centerTextHorizontally(m_titleText, centerX, 100.f);

        // score — берем из контекста
        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_scoreText.setFillColor(TEXT_COLOR);
        m_scoreText.setString("Score: "s + std::to_string(mContext.data.currentScore));
        centerTextHorizontally(m_scoreText, SCREEN_WIDTH / 2.f, 180.f);

        // label
        m_labelText.setFont(m_font);
        m_labelText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_labelText.setFillColor(TEXT_COLOR);
        m_labelText.setString("Enter your name:"s);
        centerTextHorizontally(m_labelText, centerX, 300.f);

        // name
        m_nameText.setFont(m_font);
        m_nameText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_nameText.setFillColor(sf::Color::Yellow);

        // hint
        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(14);
        m_hintText.setFillColor(HINT_COLOR);
        m_hintText.setString("ENTER - confirm, ESC - skip"s);
        centerTextHorizontally(m_hintText, centerX, SCREEN_HEIGHT - 60.f);

        m_overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        m_overlay.setFillColor(sf::Color(0, 0, 0, 150));
    }

    void NameInputState::draw()
    {
        mContext.window.draw(m_overlay);

        mContext.window.draw(m_titleText);
        mContext.window.draw(m_scoreText);
        mContext.window.draw(m_labelText);
        mContext.window.draw(m_nameText);
        mContext.window.draw(m_hintText);
    }

    bool NameInputState::update(sf::Time dt)
    {
        updateNameText();

        return false;
    }

    bool NameInputState::handleEvent(const sf::Event& event)
    {
        handleInput(event);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter && !m_playerName.empty())
            {
                mContext.data.playerName = m_playerName;

                mContext.leaderboard.insertNewRecord({ m_playerName, mContext.data.currentScore });

                mStack.popState();
                mStack.popState();
                mStack.pushState(States::Leaderboard);
                return false;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                mContext.data.playerName = DEFAULT_NAME;

                mContext.leaderboard.insertNewRecord({ DEFAULT_NAME, mContext.data.currentScore });

                mStack.popState();
                mStack.popState();
                mStack.pushState(States::Leaderboard);
                return false;
            }
        }

        if (event.type == sf::Event::TextEntered)
            return false;

        return true;
    }

    void NameInputState::handleInput(const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered)
        {
            sf::Uint32 unicode = event.text.unicode;

            if (unicode == 8 && !m_playerName.empty())
            {
                m_playerName.pop_back();
            }
            else if (unicode >= 32 && unicode < 127)
            {
                if (m_playerName.size() < NAME_INPUT_MAX_NAME_LENGTH)
                {
                    m_playerName += static_cast<char>(unicode);
                }
            }
        }
    }

    void NameInputState::updateNameText()
    {
        m_nameText.setString(m_playerName + "_");
        centerTextHorizontally(m_nameText, SCREEN_WIDTH / 2.f, 350.f);
    }

} // namespace ApplesGame