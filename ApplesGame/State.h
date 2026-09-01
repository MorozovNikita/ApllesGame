#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "GameMode.h"

namespace ApplesGame
{
    struct GameResources;
    class LeaderboardBase;
    class StateStack;

    namespace States
    {
        enum ID
        {
            None,
            Menu,
            Game,
            Pause,
            NameInput,
            Leaderboard,
            GameOver
        };
    }

    class State
    {
    public:
        using Ptr = std::unique_ptr<State>;

        struct GameData
        {
            int currentScore = 0;
            std::string playerName;
            GameMode selectedGameMode = GameMode::None;
            bool showGameOver = false;
        };

        struct Context
        {
            sf::RenderWindow& window;
            LeaderboardBase& leaderboard;
            GameResources& resources;
            GameData& data;
        };

        State(StateStack& stack, Context context);
        virtual ~State() = default;

        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        StateStack& mStack;
        Context mContext;
    };

} // namespace ApplesGame