#pragma once

#include <SFML/Audio.hpp>

#include "Apple.h"
#include "Barrier.h"
#include "Player.h"
#include "Scoreboard.h"

namespace ApplesGame
{

	class Game
	{
	public:
		void init();
		void update(const float& dt);
		void draw(sf::RenderWindow& window);

	private:
		Player player;

		std::vector<Apple> apples;
		std::vector<Barrier> barriers;

		Scoreboard scoreboard;

		// global game data
		int numEatenApples{ 0 };
		bool isPaused{ false };
		float pauseTime{ PAUSE_TIME };
		float pauseTimeLeft{ 0.f };

		// resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture barrierTexture;

		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;

		sf::Sound eatAppleSound;
		sf::Sound deathSound;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

		void initApples();
		void initBarriers();
		void resetState();
		void restart();
	};

} // namespace ApplesGame