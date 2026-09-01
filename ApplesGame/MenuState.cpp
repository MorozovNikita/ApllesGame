#include "MenuState.h"

#include <cassert>

#include "GameResources.h"
#include "StateStack.h"
#include "Constants.h"

namespace ApplesGame
{
    MenuState::MenuState(StateStack& stack, Context context)
        : State(stack, context)
        , m_font(context.resources.m_font)
        , m_leaderboard(context.leaderboard)
        , m_selectedIndex(0)
    {
        init();
    }

    void MenuState::init()
    {
        m_items =
        {
            { "1. Finite Apples + With Acceleration"s, GameMode::FiniteApples | GameMode::WithAcceleration },
            { "2. Finite Apples + Without Acceleration"s, GameMode::FiniteApples | GameMode::WithoutAcceleration },
            { "3. Infinite Apples + With Acceleration"s, GameMode::InfiniteApples | GameMode::WithAcceleration },
            { "4. Infinite Apples + Without Acceleration"s, GameMode::InfiniteApples | GameMode::WithoutAcceleration },
            { "Leaderboard"s, GameMode::None },
        };

        m_selectedIndex = 0;

        m_titleText.setString("SELECT GAME MODE");
        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(MENU_TITLE_SIZE);
        m_titleText.setFillColor(TITLE_COLOR);
        m_titleText.setPosition(SCREEN_WIDTH / 2.f, MENU_MARGIN_TOP);

        sf::FloatRect titleBounds = m_titleText.getGlobalBounds();
        m_titleText.move(SCREEN_WIDTH / 2.f - (titleBounds.left + titleBounds.width / 2.f), 0.f);

        const float centerX = SCREEN_WIDTH / 2.f;
        const float startY = MENU_MARGIN_TOP + 120.f;

        m_itemTexts.clear();
        for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
        {
            sf::Text text(m_items[i].text, m_font, MENU_ITEM_SIZE);

            float textY = startY + i * MENU_SPACING;
            text.setPosition(centerX, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(centerX - (bounds.left + bounds.width / 2.f), textY - (bounds.top + bounds.height / 2.f));

            m_itemTexts.push_back(text);
        }

        m_arrowIndicator.setPrimitiveType(sf::Triangles);
        m_arrowIndicator.resize(3);
        for (int v = 0; v < 3; ++v)
            m_arrowIndicator[v].color = sf::Color::Yellow;

        m_hintText.setString(L"Use \u2191 \u2193 to navigate, Enter to select, Esc to exit");
        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(10);
        m_hintText.setFillColor(HINT_COLOR);
        m_hintText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 40.f);

        sf::FloatRect hintBounds = m_hintText.getGlobalBounds();
        m_hintText.move(SCREEN_WIDTH / 2.f - (hintBounds.left + hintBounds.width / 2.f), 0.f);

        updateTexts();
    }

    void MenuState::draw()
    {
        mContext.window.clear(BACKGROUND_COLOR);

        mContext.window.draw(m_titleText);

        for (const auto& text : m_itemTexts)
            mContext.window.draw(text);

        const auto& selectedText = m_itemTexts[m_selectedIndex];
        sf::FloatRect bounds = selectedText.getGlobalBounds();

        float arrowX = bounds.left - MENU_ARROW_SIZE - MENU_ARROW_GAP;
        float arrowY = bounds.top + bounds.height / 2.f - MENU_ARROW_SIZE / 2.f;

        m_arrowIndicator[0].position = sf::Vector2f(arrowX, arrowY);
        m_arrowIndicator[1].position = sf::Vector2f(arrowX, arrowY + MENU_ARROW_SIZE);
        m_arrowIndicator[2].position = sf::Vector2f(arrowX + MENU_ARROW_SIZE, arrowY + MENU_ARROW_SIZE / 2.f);

        mContext.window.draw(m_arrowIndicator);

        mContext.window.draw(m_hintText);
    }

    bool MenuState::update(sf::Time dt)
    {
        return true;
    }

    bool MenuState::handleEvent(const sf::Event& event)
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
                if (m_selectedIndex == LEADERBOARD_INDEX)
                {
                    mContext.data.showGameOver = false;
                    mStack.pushState(States::Leaderboard);
                    return false;
                }

                mContext.data.selectedGameMode = m_items[m_selectedIndex].mode;
                mStack.pushState(States::Game);
                return false;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                mContext.window.close();
                return false;
            }
            else if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num4)
            {
                int index = event.key.code - sf::Keyboard::Num1;
                if (index >= 0 && index < static_cast<int>(m_items.size()))
                {
                    mContext.data.selectedGameMode = m_items[index].mode;
                    mStack.pushState(States::Game);
                    return false;
                }
            }
        }

        return true;
    }

    void MenuState::updateTexts()
    {
        for (int i = 0; i < static_cast<int>(m_itemTexts.size()); ++i)
        {
            bool isSelected = (i == m_selectedIndex);
            m_itemTexts[i].setFillColor(isSelected ? SELECTED_COLOR : TEXT_COLOR);
        }
    }

} // namespace ApplesGame