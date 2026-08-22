#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

namespace ApplesGame
{
    class NameInputScreen
    {
    public:
        void init(const sf::Font& font);
        std::string run(sf::RenderWindow& window, int score);

    private:
        void draw(sf::RenderWindow& window, int score);
        void handleInput(const sf::Event& event);
        void updateNameText();

        const sf::Font* m_font{ nullptr };
        std::string m_playerName;

        sf::Text m_titleText;
        sf::Text m_scoreText;
        sf::Text m_labelText;
        sf::Text m_nameText;
        sf::Text m_hintText;
    };

} // namespace ApplesGame