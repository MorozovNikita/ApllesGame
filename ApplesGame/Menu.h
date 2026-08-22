#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>

#include "Constants.h"
#include "GameMode.h"

namespace ApplesGame
{
    struct MenuItem
    {
        std::string text;
        GameMode mode;
    };

    class Menu
    {
    public:
        void init(const sf::Font& font);
        GameMode run(sf::RenderWindow& window);

    private:
        void draw(sf::RenderWindow& window);
        void handleInput(const sf::Event& event);
        void updateTexts();

        const sf::Font* m_font{ nullptr };
        std::vector<MenuItem> m_items;
        int m_selectedIndex{ 0 };

        std::vector<sf::Text> m_itemTexts;
        sf::Text m_titleText;
        sf::Text m_hintText;
        sf::VertexArray m_arrowIndicator;
    };

} // namespace ApplesGame