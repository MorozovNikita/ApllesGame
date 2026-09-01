#pragma once

#include "State.h"
#include "GameMode.h"
#include "LeaderboardState.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct MenuItem
    {
        std::string text;
        GameMode mode;
    };

    class MenuState : public State
    {
    public:
        MenuState(StateStack& stack, Context context);

        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;

    private:
        void init();
        void updateTexts();

        const sf::Font& m_font;
        LeaderboardBase& m_leaderboard;

        std::vector<MenuItem> m_items;
        int m_selectedIndex;

        std::vector<sf::Text> m_itemTexts;
        sf::Text m_titleText;
        sf::Text m_hintText;
        sf::VertexArray m_arrowIndicator;
    };

} // namespace ApplesGame