#include "Menu.h"

#include <cassert>

#include "Constants.h"

namespace ApplesGame
{
    void Menu::init()
    {
        assert(font.loadFromFile(RESOURCES_PATH + "\\Fonts\\PressStart2P-Regular.ttf"));

        items = { { "1. Finite Apples + With Acceleration",GameMode::FiniteApples | GameMode::WithAcceleration },
                  { "2. Finite Apples + Without Acceleration", GameMode::FiniteApples | GameMode::WithoutAcceleration },
                  { "3. Infinite Apples + With Acceleration", GameMode::InfiniteApples | GameMode::WithAcceleration },
                  { "4. Infinite Apples + Without Acceleration", GameMode::InfiniteApples | GameMode::WithoutAcceleration },
                };

        selectedIndex = 0;

        titleText.setString("SELECT GAME MODE");
        titleText.setFont(font);
        titleText.setCharacterSize(TITLE_SIZE);
        titleText.setFillColor(titleColor);
        titleText.setPosition(SCREEN_WIDTH / 2.f, MARGIN_TOP);

        sf::FloatRect titleBounds = titleText.getGlobalBounds();
        titleText.move(SCREEN_WIDTH / 2.f - (titleBounds.left + titleBounds.width / 2.f), 0.f);

        const float centerX = SCREEN_WIDTH / 2.f;
        const float startY = MARGIN_TOP + 120.f;

        itemTexts.clear();
        for (int i = 0; i < static_cast<int>(items.size()); ++i)
        {
            sf::Text text(items[i].text, font, ITEM_SIZE);

            float textY = startY + i * SPACING;
            text.setPosition(centerX, textY);

            sf::FloatRect bounds = text.getGlobalBounds();
            text.move(centerX - (bounds.left + bounds.width / 2.f),
                textY - (bounds.top + bounds.height / 2.f));

            itemTexts.push_back(text);
        }

        arrowIndicator.setPrimitiveType(sf::Triangles);
        arrowIndicator.resize(3);
        for (int v = 0; v < 3; ++v)
            arrowIndicator[v].color = sf::Color::Yellow;

        hintText.setString(L"Use \u2191 \u2193 to navigate, Enter to select, Esc to exit");
        hintText.setFont(font);
        hintText.setCharacterSize(10);
        hintText.setFillColor(hintColor);
        hintText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 40.f);

        sf::FloatRect hintBounds = hintText.getGlobalBounds();
        hintText.move(SCREEN_WIDTH / 2.f - (hintBounds.left + hintBounds.width / 2.f), 0.f);

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
                        selectedMode = items[selectedIndex].mode;
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
                        if (index >= 0 && index < static_cast<int>(items.size()))
                        {
                            selectedMode = items[index].mode;
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
                --selectedIndex;
                if (selectedIndex < 0)
                    selectedIndex = static_cast<int>(items.size()) - 1;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                ++selectedIndex;
                if (selectedIndex >= static_cast<int>(items.size()))
                    selectedIndex = 0;
            }

            updateTexts();
        }
    }

    void Menu::updateTexts()
    {
        for (int i = 0; i < static_cast<int>(itemTexts.size()); ++i)
        {
            bool isSelected = (i == selectedIndex);
            itemTexts[i].setFillColor(isSelected ? selectedColor : normalColor);
        }
    }

    void Menu::draw(sf::RenderWindow& window)
    {
        window.clear(backgroundColor);

        window.draw(titleText);

        for (const auto& text : itemTexts)
            window.draw(text);

        const auto& selectedText = itemTexts[selectedIndex];
        sf::FloatRect bounds = selectedText.getGlobalBounds();

        float arrowX = bounds.left - ARROW_SIZE - ARROW_GAP;
        float arrowY = bounds.top + bounds.height / 2.f - ARROW_SIZE / 2.f;

        arrowIndicator[0].position = sf::Vector2f(arrowX, arrowY);
        arrowIndicator[1].position = sf::Vector2f(arrowX, arrowY + ARROW_SIZE);
        arrowIndicator[2].position = sf::Vector2f(arrowX + ARROW_SIZE, arrowY + ARROW_SIZE / 2.f);

        window.draw(arrowIndicator);

        window.draw(hintText);

        window.display();
    }

} // namespace ApplesGame