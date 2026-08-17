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

	// game initialization
	ApplesGame::Game game;
	game.init();

	// select mode
	GameMode selectedMode = game.selectMode(window);
	if (selectedMode == GameMode::None)
		return 0;

	// init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// main loop
	while (window.isOpen())
	{
		// delta time
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float dt = currentTime - lastTime;
		lastTime = currentTime;
		 
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
				window.close();
				break;
			}
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
