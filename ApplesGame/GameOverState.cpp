#include "GameOverState.h"

#include "StateStack.h"
#include "Constants.h"
#include "GameResources.h"

namespace ApplesGame
{
    GameOverState::GameOverState(StateStack& stack, Context& context)
        : State(stack, context)
        , m_font(context.resources.m_font)
        , m_selectedIndex(0)
    {
        m_items =
        {
            "Play Again"s,
            "Main Menu"s,
        };

        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(MENU_TITLE_SIZE);
        m_titleText.setFillColor(TITLE_COLOR);
        m_titleText.setString("GAME OVER");
        m_titleText.setPosition(SCREEN_WIDTH / 2.f, MENU_MARGIN_TOP);

        sf::FloatRect titleBounds = m_titleText.getGlobalBounds();
        m_titleText.move(SCREEN_WIDTH / 2.f - (titleBounds.left + titleBounds.width / 2.f), 0.f);

        const float centerX = SCREEN_WIDTH / 2.f;
        const float startY = MENU_MARGIN_TOP + 120.f;

        m_itemTexts.clear();
        for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
        {
            sf::Text text(m_items[i], m_font, MENU_ITEM_SIZE);

            float textY = startY + i * MENU_SPACING;
            text.setPosition(centerX, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(centerX - (bounds.left + bounds.width / 2.f), textY - (bounds.top + bounds.height / 2.f));

            m_itemTexts.push_back(text);
        }

        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(10);
        m_hintText.setFillColor(HINT_COLOR);
        m_hintText.setString("UP/DOWN - navigate, ENTER - select");
        m_hintText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 40.f);

        sf::FloatRect hintBounds = m_hintText.getGlobalBounds();
        m_hintText.move(SCREEN_WIDTH / 2.f - (hintBounds.left + hintBounds.width / 2.f), 0.f);

        updateTexts();
    }

    void GameOverState::draw()
    {
        mContext.window.clear(BACKGROUND_COLOR);

        mContext.window.draw(m_titleText);

        for (const auto& text : m_itemTexts)
            mContext.window.draw(text);

        mContext.window.draw(m_hintText);
    }

    bool GameOverState::update(sf::Time dt)
    {
        return false;
    }

    bool GameOverState::handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                --m_selectedIndex;
                if (m_selectedIndex < 0)
                    m_selectedIndex = static_cast<int>(m_items.size()) - 1;
                updateTexts();
                return false;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                ++m_selectedIndex;
                if (m_selectedIndex >= static_cast<int>(m_items.size()))
                    m_selectedIndex = 0;
                updateTexts();
                return false;
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                mContext.data.showGameOver = false;

                if (m_selectedIndex == 0)
                {
                    mStack.clearStates();
                    mStack.pushState(States::Menu);
                    mStack.pushState(States::Game);
                }
                else if (m_selectedIndex == 1)
                {
                    mStack.clearStates();
                    mStack.pushState(States::Menu);
                }
                return false;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                mStack.popState();
                return false;
            }
        }

        return true;
    }

    void GameOverState::updateTexts()
    {
        for (int i = 0; i < static_cast<int>(m_itemTexts.size()); ++i)
        {
            bool isSelected = (i == m_selectedIndex);
            m_itemTexts[i].setFillColor(isSelected ? SELECTED_COLOR : TEXT_COLOR);
        }
    }

} // namespace ApplesGame