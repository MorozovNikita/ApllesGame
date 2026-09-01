#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "State.h"
#include "GameMode.h"
#include "Player.h"
#include "Apple.h"
#include "Barrier.h"
#include "Scoreboard.h"

namespace ApplesGame
{
    struct GameResources;

    class GameState : public State
    {
    public:
        GameState(StateStack& stack, Context& context);

        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(const sf::Event& event) override;

    private:
        void initApples();
        void initBarriers();
        void resetState();
        void restart(bool isWin = false);

        void randomizeApplesCount();

        bool isInfiniteApplesMode() const;
        bool isWithAccelerationMode() const;

        bool m_isDead = false;

        GameResources& m_resources;
        GameMode m_currentMode;

        Player m_player;

        std::vector<Apple> m_apples;
        std::vector<Barrier> m_barriers;

        int m_numEatenApples;
        int m_currentApplesCount;

        Scoreboard m_scoreboard;
    };

} // namespace ApplesGame