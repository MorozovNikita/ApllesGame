#include "Game.h"

#include <cassert>
#include <random>

namespace ApplesGame
{

	void Game::init()
	{
		assert(m_playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(m_appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(m_barrierTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(m_backgroundTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));

		assert(m_eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(m_deathSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(m_winSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Win.wav"));

		assert(m_font.loadFromFile(RESOURCES_PATH + "\\Fonts\\PressStart2P-Regular.ttf"));

		m_eatAppleSound.setBuffer(m_eatAppleSoundBuffer);
		m_deathSound.setBuffer(m_deathSoundBuffer);
		m_winSound.setBuffer(m_winSoundBuffer);

		m_backgroundSprite.setTexture(m_backgroundTexture);

		const auto textureSize = m_backgroundTexture.getSize();
		const float scaleX = SCREEN_WIDTH / static_cast<float>(textureSize.x);
		const float scaleY = SCREEN_HEIGHT / static_cast<float>(textureSize.y);
		m_backgroundSprite.setScale(scaleX, scaleY);

		// tmp
		m_leaderBoard.generate(15);

		m_menu.init(m_font, m_leaderBoard);
		m_nameInput.init(m_font);
	}

	void Game::update(const float& dt)
	{
		if (m_isPaused)
		{
			m_pauseTimeLeft -= dt;

			if (m_pauseTimeLeft <= 0.f)
				m_isPaused = false;
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_player.m_direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_player.m_direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_player.m_direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_player.m_direction = PlayerDirection::Down;
			}

			switch (m_player.m_direction)
			{
			case PlayerDirection::Right:
				m_player.m_position.x += m_player.m_speed * dt;
				break;
			case PlayerDirection::Up:
				m_player.m_position.y -= m_player.m_speed * dt;
				break;
			case PlayerDirection::Left:
				m_player.m_position.x -= m_player.m_speed * dt;
				break;
			case PlayerDirection::Down:
				m_player.m_position.y += m_player.m_speed * dt;
				break;
			default:
				break;
			}

			m_player.updateSprite(dt);

			if (m_player.m_position.x - PLAYER_SIZE / 2.f < 0.f || m_player.m_position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH
				|| m_player.m_position.y - PLAYER_SIZE / 2.f < 0.f || m_player.m_position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				restart();
				return;
			}

			// find player collisions with apples
			for (Apple& apple : m_apples)
			{
				if (apple.m_isEaten)
					continue;

				if (isCirclesCollide(m_player.m_position, PLAYER_SIZE / 2.f, apple.m_position, APPLE_SIZE / 2.f))
				{
					++m_numEatenApples;

					if (isWithAccelerationMode())
						m_player.m_speed += ACCELERATION;

					if (isInfiniteApplesMode())
					{
						apple.m_position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
						m_scoreboard.update(m_numEatenApples);
					}
					else
					{
						// mark the apple as eaten so that don't have to process the collision
						apple.m_isEaten = true;
						apple.m_position = { -100.f, -100.f };
						m_scoreboard.update(m_numEatenApples, m_currentApplesCount);
					}

					m_eatAppleSound.play();
				}
			}

			if (!isInfiniteApplesMode() && m_numEatenApples >= m_apples.size())
			{
				restart(true);
				return;
			}

			// find player collisions with barriers
			for (int i = 0; i < NUM_BARRIERS; ++i)
			{
				if (isRectanglesCollide(m_player.m_position, { PLAYER_SIZE, PLAYER_SIZE }, m_barriers[i].m_position, { BARRIER_SIZE, BARRIER_SIZE }))
				{
					restart();
					return;
				}
			}
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		window.draw(m_backgroundSprite);

		m_player.draw(window);

		for (auto& apple : m_apples)
			apple.draw(window);

		for (auto& barrier : m_barriers)
			barrier.draw(window);

		m_scoreboard.draw(window);
	}

	void Game::setWindow(const sf::RenderWindow& window)
	{
		m_window = const_cast<sf::RenderWindow*>(&window);
	}

	GameMode Game::selectMode(sf::RenderWindow& window)
	{
		m_currentMode = m_menu.run(window);

		if (m_currentMode != GameMode::None)
		{
			resetState();

			m_isPaused = true;
			m_pauseTimeLeft = m_pauseTime;
		}

		return m_currentMode;
	}

	void Game::initApples()
	{
		m_apples.resize(m_currentApplesCount);
		for (Apple& apple : m_apples)
			apple.init(m_appleTexture);
	}

	void Game::initBarriers()
	{
		m_barriers.resize(NUM_BARRIERS);
		for (Barrier& barrier : m_barriers)
			barrier.init(m_barrierTexture);
	}

	void Game::resetState()
	{
		randomizeApplesCount();

		m_player.init(m_playerTexture);
		initApples();
		initBarriers();
		m_scoreboard.init(m_font, (isInfiniteApplesMode() ? 0 : m_currentApplesCount));

		m_numEatenApples = 0;
		m_isPaused = false;
		m_pauseTimeLeft = 0.f;
	}

	void Game::restart(bool isWin)
	{
		if (isWin)
			m_winSound.play();
		else
			m_deathSound.play();
			
		if (m_leaderBoard.getScoreMinValue() < m_numEatenApples)
		{
			auto name = m_nameInput.run(*m_window, m_numEatenApples);
			m_leaderBoard.insertNewRecord({name, m_numEatenApples});
		}

		resetState();

		m_isPaused = true;
		m_pauseTimeLeft = m_pauseTime;
	}

	void Game::randomizeApplesCount()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());

		int min{ 0 }, max{ 0 };
		if (isInfiniteApplesMode())
		{
			min = MIN_APPLES_INFINITE;
			max = MAX_APPLES_INFINITE;
		}
		else
		{
			min = MIN_APPLES_FINITE;
			max = MAX_APPLES_FINITE;
		}

		std::uniform_int_distribution<int> dist(min, max);
		m_currentApplesCount = dist(gen);
	}

	bool Game::isInfiniteApplesMode() const
	{
		return hasFlag(m_currentMode, GameMode::InfiniteApples);
	}

	bool Game::isWithAccelerationMode() const
	{
		return hasFlag(m_currentMode, GameMode::WithAcceleration);
	}

} // namespace ApplesGame
