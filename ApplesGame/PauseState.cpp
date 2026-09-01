#include "PauseState.h"

#include "StateStack.h"
#include "Constants.h"
#include "GameResources.h"

namespace ApplesGame
{
    PauseState::PauseState(StateStack& stack, Context& context)
        : State(stack, context)
        , m_font(context.resources.m_font)
        , m_selectedIndex(0)
    {
        m_items =
        {
            "Resume Game"s,
            "Exit to Menu"s,
        };

        m_backgroundShape.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        m_backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(MENU_TITLE_SIZE);
        m_titleText.setFillColor(TITLE_COLOR);
        m_titleText.setString("PAUSE");

        sf::FloatRect titleBounds = m_titleText.getGlobalBounds();
        m_titleText.setPosition(SCREEN_WIDTH / 2.f - titleBounds.width / 2.f, MENU_MARGIN_TOP);

        const float startY = MENU_MARGIN_TOP + 100.f;
        for (size_t i = 0; i < m_items.size(); ++i)
        {
            sf::Text text(m_items[i], m_font, MENU_ITEM_SIZE);
            text.setFillColor(TEXT_COLOR);
            text.setOutlineColor(sf::Color::Yellow);

            float textY = startY + i * MENU_SPACING;
            text.setPosition(SCREEN_WIDTH / 2.f, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(SCREEN_WIDTH / 2.f - (bounds.left + bounds.width / 2.f), textY - (bounds.top + bounds.height / 2.f));

            m_itemTexts.push_back(text);
        }

        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(10);
        m_hintText.setFillColor(HINT_COLOR);
        m_hintText.setString("UP/DOWN - navigate, ENTER - select, ESC - resume");

        sf::FloatRect hintBounds = m_hintText.getGlobalBounds();
        m_hintText.setPosition(SCREEN_WIDTH / 2.f - hintBounds.width / 2.f, SCREEN_HEIGHT - 40.f);

        updateTexts();
    }

    void PauseState::draw()
    {
        mContext.window.draw(m_backgroundShape);
        mContext.window.draw(m_titleText);

        for (const auto& text : m_itemTexts)
            mContext.window.draw(text);

        mContext.window.draw(m_hintText);
    }

    bool PauseState::update(sf::Time dt)
    {
        return false;
    }

    bool PauseState::handleEvent(const sf::Event& event)
    {
        handleInput(event);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                if (m_selectedIndex == 0)
                {
                    mStack.popState();
                    return false;
                }
                else if (m_selectedIndex == 1)
                {
                    mStack.popState();
                    mStack.popState();

                    return false;
                }
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                mStack.popState();
                return false;
            }
        }

        return false;
    }

    void PauseState::handleInput(const sf::Event& event)
    {
        if (event.type != sf::Event::KeyPressed)
            return;

        if (event.key.code == sf::Keyboard::Up)
        {
            --m_selectedIndex;
            if (m_selectedIndex < 0)
                m_selectedIndex = static_cast<int>(m_items.size()) - 1;
            updateTexts();
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            ++m_selectedIndex;
            if (m_selectedIndex >= static_cast<int>(m_items.size()))
                m_selectedIndex = 0;
            updateTexts();
        }
    }

    void PauseState::updateTexts()
    {
        for (size_t i = 0; i < m_itemTexts.size(); ++i)
        {
            const bool isSelected = (static_cast<int>(i) == m_selectedIndex);

            if (isSelected)
                m_itemTexts[i].setFillColor(SELECTED_COLOR);
            else
                m_itemTexts[i].setFillColor(TEXT_COLOR);
        }
    }

} // namespace ApplesGame