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
        void init();
        GameMode run(sf::RenderWindow& window);

    private:
        void draw(sf::RenderWindow& window);
        void handleInput(const sf::Event& event);
        void updateTexts();

        sf::Font font;
        std::vector<MenuItem> items;
        int selectedIndex{ 0 };

        std::vector<sf::Text> itemTexts;
        sf::Text titleText;
        sf::Text hintText;
        sf::VertexArray arrowIndicator;

        sf::Color backgroundColor{ sf::Color(20, 20, 40) };
        sf::Color normalColor{ sf::Color(200, 200, 200) };
        sf::Color selectedColor{ sf::Color::Yellow };
        sf::Color titleColor{ sf::Color::White };
        sf::Color hintColor{ sf::Color(150, 150, 150) };
    };

} // namespace ApplesGame