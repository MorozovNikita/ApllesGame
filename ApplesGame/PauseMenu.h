#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

namespace ApplesGame
{
    enum class PauseMenuResult
    {
        None,
        Continue,
        ExitToMenu,
    };

    class PauseMenu
    {
    public:
        PauseMenu(const sf::Font& font);

        PauseMenuResult run(sf::RenderWindow& window);

    private:
        void handleInput(const sf::Event& event);
        void updateTexts();
        void draw(sf::RenderWindow& window);

        const sf::Font& m_font;
        int m_selectedIndex{ 0 };

        std::vector<std::string> m_items;
        std::vector<sf::Text> m_itemTexts;
        sf::Text m_titleText;
        sf::Text m_hintText;
    };
}