#include "Menu.h"

#include <cassert>

#include "Constants.h"

namespace ApplesGame
{
    void Menu::init(const sf::Font& font)
    {
        m_font = &font;
        m_leaderboard.init(font);

        m_items = { { "1. Finite Apples + With Acceleration",GameMode::FiniteApples | GameMode::WithAcceleration },
                  { "2. Finite Apples + Without Acceleration", GameMode::FiniteApples | GameMode::WithoutAcceleration },
                  { "3. Infinite Apples + With Acceleration", GameMode::InfiniteApples | GameMode::WithAcceleration },
                  { "4. Infinite Apples + Without Acceleration", GameMode::InfiniteApples | GameMode::WithoutAcceleration },
                  { "Leaderboard", GameMode::None },
                };

        m_selectedIndex = 0;

        m_titleText.setString("SELECT GAME MODE");
        m_titleText.setFont(*m_font);
        m_titleText.setCharacterSize(MENU_TITLE_SIZE);
        m_titleText.setFillColor(titleColor);
        m_titleText.setPosition(SCREEN_WIDTH / 2.f, MENU_MARGIN_TOP);

        sf::FloatRect titleBounds = m_titleText.getGlobalBounds();
        m_titleText.move(SCREEN_WIDTH / 2.f - (titleBounds.left + titleBounds.width / 2.f), 0.f);

        const float centerX = SCREEN_WIDTH / 2.f;
        const float startY = MENU_MARGIN_TOP + 120.f;

        m_itemTexts.clear();
        for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
        {
            sf::Text text(m_items[i].text, *m_font, MENU_ITEM_SIZE);

            float textY = startY + i * MENU_SPACING;
            text.setPosition(centerX, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(centerX - (bounds.left + bounds.width / 2.f),
                textY - (bounds.top + bounds.height / 2.f));

            m_itemTexts.push_back(text);
        }

        m_arrowIndicator.setPrimitiveType(sf::Triangles);
        m_arrowIndicator.resize(3);
        for (int v = 0; v < 3; ++v)
            m_arrowIndicator[v].color = sf::Color::Yellow;

        m_hintText.setString(L"Use \u2191 \u2193 to navigate, Enter to select, Esc to exit");
        m_hintText.setFont(*m_font);
        m_hintText.setCharacterSize(10);
        m_hintText.setFillColor(hintColor);
        m_hintText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 40.f);

        sf::FloatRect hintBounds = m_hintText.getGlobalBounds();
        m_hintText.move(SCREEN_WIDTH / 2.f - (hintBounds.left + hintBounds.width / 2.f), 0.f);

        updateTexts();
    }

    GameMode Menu::run(sf::RenderWindow& window)
    {
        bool running = true;
        GameMode selectedMode = GameMode::None;

        while (running && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return GameMode::None;
                }

                handleInput(event);

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (m_selectedIndex == LEADERBOARD_INDEX)
                        {
                            m_leaderboard.run(window);
                            continue;
                        }

                        selectedMode = m_items[m_selectedIndex].mode;
                        running = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                        return GameMode::None;
                    }
                    else if (event.key.code >= sf::Keyboard::Num1 &&
                        event.key.code <= sf::Keyboard::Num4)
                    {
                        int index = event.key.code - sf::Keyboard::Num1;
                        if (index >= 0 && index < static_cast<int>(m_items.size()))
                        {
                            selectedMode = m_items[index].mode;
                            running = false;
                        }
                    }
                }
            }

            draw(window);
        }

        return selectedMode;
    }

    void Menu::handleInput(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                --m_selectedIndex;
                if (m_selectedIndex < 0)
                    m_selectedIndex = static_cast<int>(m_items.size()) - 1;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                ++m_selectedIndex;
                if (m_selectedIndex >= static_cast<int>(m_items.size()))
                    m_selectedIndex = 0;
            }

            updateTexts();
        }
    }

    void Menu::updateTexts()
    {
        for (int i = 0; i < static_cast<int>(m_itemTexts.size()); ++i)
        {
            bool isSelected = (i == m_selectedIndex);
            m_itemTexts[i].setFillColor(isSelected ? selectedColor : textColor);
        }
    }

    void Menu::draw(sf::RenderWindow& window)
    {
        window.clear(backgroundColor);

        window.draw(m_titleText);

        for (const auto& text : m_itemTexts)
            window.draw(text);

        const auto& selectedText = m_itemTexts[m_selectedIndex];
        sf::FloatRect bounds = selectedText.getGlobalBounds();

        float arrowX = bounds.left - MENU_ARROW_SIZE - MENU_ARROW_GAP;
        float arrowY = bounds.top + bounds.height / 2.f - MENU_ARROW_SIZE / 2.f;

        m_arrowIndicator[0].position = sf::Vector2f(arrowX, arrowY);
        m_arrowIndicator[1].position = sf::Vector2f(arrowX, arrowY + MENU_ARROW_SIZE);
        m_arrowIndicator[2].position = sf::Vector2f(arrowX + MENU_ARROW_SIZE, arrowY + MENU_ARROW_SIZE / 2.f);

        window.draw(m_arrowIndicator);

        window.draw(m_hintText);

        window.display();
    }

} // namespace ApplesGame