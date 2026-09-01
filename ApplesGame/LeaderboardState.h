#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "LeaderboardBase.h"

namespace ApplesGame
{
    class LeaderboardState : public State
    {
    public:
        LeaderboardState(StateStack& stack, Context context);

        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;

    private:
        void init();

        const sf::Font& m_font;
        LeaderboardBase& m_leaderboard;

        sf::Text m_titleText;
        sf::Text m_hintText;

        sf::Text createText(const sf::Font& font, int size, sf::Color color);
    };

} // namespace ApplesGame