#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "State.h"
#include "Constants.h"

namespace ApplesGame
{
    class NameInputState : public State
    {
    public:
        NameInputState(StateStack& stack, Context& context);

        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;

    private:
        void init();
        void handleInput(const sf::Event& event);
        void updateNameText();

        const sf::Font& m_font;
        std::string m_playerName;

        sf::Text m_titleText;
        sf::Text m_scoreText;
        sf::Text m_labelText;
        sf::Text m_nameText;
        sf::Text m_hintText;

        sf::RectangleShape m_overlay;
    };

} // namespace ApplesGame