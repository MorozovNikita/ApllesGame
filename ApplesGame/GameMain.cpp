// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);

	// init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// gameResources initialization
	GameResources gameResources;

	// game initialization
	ApplesGame::Game game(window, gameResources);

	// select mode
	GameMode selectedMode = game.selectMode(window);
	if (selectedMode == GameMode::None)
		return 0;

	// init game clock
	sf::Clock gameClock;

	// main loop
	while (window.isOpen())
	{
		// delta time
		float dt = gameClock.restart().asSeconds();
		 
		// read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				selectedMode = game.selectMode(window);
				if (selectedMode == GameMode::None)
					return 0;

				gameClock.restart();
				dt = 0.f;
				break;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Space)
				game.pause(window);
		}

		// update game state
		game.update(dt);

		// draw game
		window.clear();
		game.draw(window);
		window.display();
	}

	// deinitialization

	return 0;
}
