#include <SFML/Graphics.hpp>

#include "StateStack.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "LeaderboardBase.h"
#include "NameInputState.h"
#include "GameResources.h"
#include "GlobalLeaderboard.h"
#include "GameOverState.h"

int main()
{
    using namespace ApplesGame;
    srand((int)time(nullptr));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

    GameResources gameResources;
    auto leaderboard = std::make_unique<GlobalLeaderboard>(MAX_RECORDS);

    State::GameData gameData;
    State::Context context{window, *leaderboard, gameResources, gameData};

    StateStack stateStack(context);

    stateStack.registerState<MenuState>(States::Menu);
    stateStack.registerState<GameState>(States::Game);
    stateStack.registerState<PauseState>(States::Pause);
    stateStack.registerState<LeaderboardState>(States::Leaderboard);
    stateStack.registerState<NameInputState>(States::NameInput);
    stateStack.registerState<GameOverState>(States::GameOver);

    stateStack.pushState(States::Menu);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            stateStack.handleEvent(event);
        }

        stateStack.update(dt);

        window.clear();
        stateStack.draw();
        window.display();

        if (stateStack.isEmpty())
            window.close();
    }

    return 0;
}