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

	class Game
	{
	public:
		void init();
		void update(const float& dt);
		void draw(sf::RenderWindow& window);
		void setWindow(const sf::RenderWindow& window);

		GameMode selectMode(sf::RenderWindow& window);

	private:
		Player m_player;

		std::vector<Apple> m_apples;
		std::vector<Barrier> m_barriers;

		sf::RenderWindow* m_window{ nullptr };

		Scoreboard m_scoreboard;
		Menu m_menu;
		NameInputScreen m_nameInput;

		// global game data
		int m_numEatenApples{ 0 };
		int m_currentApplesCount{ 0 };
		bool m_isPaused{ false };
		float m_pauseTime{ PAUSE_TIME };
		float m_pauseTimeLeft{ 0.f };

		GameMode m_currentMode{ GameMode::None };

		// resources
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

		void initApples();
		void initBarriers();
		void resetState();
		void restart(bool isWin = false);

		void randomizeApplesCount();

		bool isInfiniteApplesMode() const;
		bool isWithAccelerationMode() const;
	};

} // namespace ApplesGame