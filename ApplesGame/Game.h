#pragma once

#include <SFML/Audio.hpp>

#include "Apple.h"
#include "Barrier.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Menu.h"
#include "NameInputScreen.h"

namespace ApplesGame
{
	struct GameResources
	{
		GameResources();
		~GameResources() = default;

		sf::Texture m_playerTexture;
		sf::Texture m_appleTexture;
		sf::Texture m_barrierTexture;

		sf::SoundBuffer m_eatAppleSoundBuffer;
		sf::SoundBuffer m_deathSoundBuffer;
		sf::SoundBuffer m_winSoundBuffer;

		sf::Sound m_eatAppleSound;
		sf::Sound m_deathSound;
		sf::Sound m_winSound;

		sf::Texture m_backgroundTexture;
		sf::Sprite m_backgroundSprite;

		sf::Font m_font;
	};

	class Game
	{
	public:
		Game(sf::RenderWindow& window, GameResources& resources);
		~Game() = default;

		void update(const float& dt);
		void draw(sf::RenderWindow& window);

		GameMode selectMode(sf::RenderWindow& window);

	private:
		sf::RenderWindow& m_window;

		// resources
		GameResources& m_resources;

		Leaderboard m_leaderBoard;

		Menu m_menu;
		NameInputScreen m_nameInput;

		Player m_player;

		std::vector<Apple> m_apples;
		std::vector<Barrier> m_barriers;

		// global game data
		int m_numEatenApples{ 0 };
		int m_currentApplesCount{ 0 };
		bool m_isPaused{ false };
		float m_pauseTime{ PAUSE_TIME };
		float m_pauseTimeLeft{ 0.f };

		GameMode m_currentMode{ GameMode::None };

		Scoreboard m_scoreboard;

		void initApples();
		void initBarriers();
		void resetState();
		void restart(bool isWin = false);

		void randomizeApplesCount();

		bool isInfiniteApplesMode() const;
		bool isWithAccelerationMode() const;
	};

} // namespace ApplesGame