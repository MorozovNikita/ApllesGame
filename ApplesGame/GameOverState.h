#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "State.h"

namespace ApplesGame
{
    class GameOverState : public State
    {
    public:
        GameOverState(StateStack& stack, Context& context);

        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;

    private:
        void updateTexts();

        const sf::Font& m_font;
        int m_selectedIndex;

        std::vector<std::string> m_items;
        std::vector<sf::Text> m_itemTexts;
        sf::Text m_titleText;
        sf::Text m_hintText;
    };

} // namespace ApplesGame