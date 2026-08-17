#pragma once

#include <SFML/Audio.hpp>

#include "Apple.h"
#include "Barrier.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Menu.h"

namespace ApplesGame
{

	class Game
	{
	public:
		void init();
		void update(const float& dt);
		void draw(sf::RenderWindow& window);

		GameMode selectMode(sf::RenderWindow& window);

	private:
		Player player;

		std::vector<Apple> apples;
		std::vector<Barrier> barriers;

		Scoreboard scoreboard;
		Menu menu;

		// global game data
		int numEatenApples{ 0 };
		bool isPaused{ false };
		float pauseTime{ PAUSE_TIME };
		float pauseTimeLeft{ 0.f };

		GameMode currentMode{ GameMode::None };

		// resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture barrierTexture;

		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;
		sf::SoundBuffer winSoundBuffer;

		sf::Sound eatAppleSound;
		sf::Sound deathSound;
		sf::Sound winSound;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

		void initApples();
		void initBarriers();
		void resetState();
		void restart(bool isWin = false);

		bool isInfiniteApplesMode() const;
		bool isWithAccelerationMode() const;
	};

} // namespace ApplesGame