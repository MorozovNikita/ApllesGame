#include "PauseMenu.h"

#include "Constants.h"

namespace ApplesGame
{
    PauseMenu::PauseMenu(const sf::Font& font)
        : m_font(font)
    {
        m_items = 
        {
            "Resume Game",
            "Exit to Menu",
        };

        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(MENU_TITLE_SIZE);
        m_titleText.setFillColor(titleColor);
        m_titleText.setString("PAUSE");

        sf::FloatRect titleBounds = m_titleText.getGlobalBounds();
        m_titleText.setPosition(SCREEN_WIDTH / 2.f - titleBounds.width / 2.f, MENU_MARGIN_TOP);

        const float startY = MENU_MARGIN_TOP + 100.f;
        for (size_t i = 0; i < m_items.size(); ++i)
        {
            sf::Text text(m_items[i], m_font, MENU_ITEM_SIZE);
            text.setFillColor(textColor);
            text.setOutlineColor(sf::Color::Yellow);

            float textY = startY + i * MENU_SPACING;
            text.setPosition(SCREEN_WIDTH / 2.f, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(SCREEN_WIDTH / 2.f - (bounds.left + bounds.width / 2.f), textY - (bounds.top + bounds.height / 2.f));

            m_itemTexts.push_back(text);
        }

        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(10);
        m_hintText.setFillColor(hintColor);
        m_hintText.setString("UP/DOWN - navigate, ENTER - select, ESC - resume");

        sf::FloatRect hintBounds = m_hintText.getGlobalBounds();
        m_hintText.setPosition(SCREEN_WIDTH / 2.f - hintBounds.width / 2.f, SCREEN_HEIGHT - 40.f);

        updateTexts();
    }

    PauseMenuResult PauseMenu::run(sf::RenderWindow& window)
    {
        m_selectedIndex = 0;
        updateTexts();

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return PauseMenuResult::None;
                }

                handleInput(event);

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (m_selectedIndex == 0)
                            return PauseMenuResult::Continue;
                        else if (m_selectedIndex == 1)
                            return PauseMenuResult::ExitToMenu;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        return PauseMenuResult::Continue;
                    }
                }
            }

            draw(window);
        }

        return PauseMenuResult::None;
    }

    void PauseMenu::handleInput(const sf::Event& event)
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

    void PauseMenu::updateTexts()
    {
        for (size_t i = 0; i < m_itemTexts.size(); ++i)
        {
            const bool isSelected = (static_cast<int>(i) == m_selectedIndex);

            if (isSelected)
                m_itemTexts[i].setFillColor(selectedColor);
            else
                m_itemTexts[i].setFillColor(textColor);
        }
    }

    void PauseMenu::draw(sf::RenderWindow& window)
    {
        window.clear(backgroundColor);

        window.draw(m_titleText);

        for (const auto& text : m_itemTexts)
            window.draw(text);

        window.draw(m_hintText);

        window.display();
    }
}