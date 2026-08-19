#include "Game.h"

#include <cassert>
#include <random>

namespace ApplesGame
{

	void Game::init()
	{
		assert(playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(barrierTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(backgroundTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));

		assert(eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(deathSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(winSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Win.wav"));

		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		deathSound.setBuffer(deathSoundBuffer);
		winSound.setBuffer(winSoundBuffer);

		backgroundSprite.setTexture(backgroundTexture);

		const auto textureSize = backgroundTexture.getSize();
		const float scaleX = SCREEN_WIDTH / static_cast<float>(textureSize.x);
		const float scaleY = SCREEN_HEIGHT / static_cast<float>(textureSize.y);
		backgroundSprite.setScale(scaleX, scaleY);

		menu.init();
	}

	void Game::update(const float& dt)
	{
		if (isPaused)
		{
			pauseTimeLeft -= dt;

			if (pauseTimeLeft <= 0.f)
				isPaused = false;
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player.direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player.direction = PlayerDirection::Down;
			}

			switch (player.direction)
			{
			case PlayerDirection::Right:
				player.position.x += player.speed * dt;
				break;
			case PlayerDirection::Up:
				player.position.y -= player.speed * dt;
				break;
			case PlayerDirection::Left:
				player.position.x -= player.speed * dt;
				break;
			case PlayerDirection::Down:
				player.position.y += player.speed * dt;
				break;
			default:
				break;
			}

			player.updateSprite(dt);

			if (player.position.x - PLAYER_SIZE / 2.f < 0.f || player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH
				|| player.position.y - PLAYER_SIZE / 2.f < 0.f || player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				restart();
				return;
			}

			// find player collisions with apples
			for (Apple& apple : apples)
			{
				if (apple.isEaten)
					continue;

				if (isCirclesCollide(player.position, PLAYER_SIZE / 2.f, apple.position, APPLE_SIZE / 2.f))
				{
					++numEatenApples;

					if (isWithAccelerationMode())
						player.speed += ACCELERATION;

					if (isInfiniteApplesMode())
					{
						apple.position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else
					{
						// mark the apple as eaten so that don't have to process the collision
						apple.isEaten = true;
						apple.position = { -100.f, -100.f };
					}

					eatAppleSound.play();
					scoreboard.update(numEatenApples);
				}
			}

			if (!isInfiniteApplesMode() && numEatenApples >= apples.size())
			{
				restart(true);
				return;
			}

			// find player collisions with barriers
			for (int i = 0; i < NUM_BARRIERS; ++i)
			{
				if (isRectanglesCollide(player.position, { PLAYER_SIZE, PLAYER_SIZE }, barriers[i].position, { BARRIER_SIZE, BARRIER_SIZE }))
				{
					restart();
					return;
				}
			}
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		window.draw(backgroundSprite);

		player.draw(window);

		for (auto& apple : apples)
			apple.draw(window);

		for (auto& barrier : barriers)
			barrier.draw(window);

		scoreboard.draw(window);
	}

	GameMode Game::selectMode(sf::RenderWindow& window)
	{
		currentMode = menu.run(window);

		if (currentMode != GameMode::None)
			resetState();

		return currentMode;
	}

	void Game::initApples()
	{
		apples.resize(currentApplesCount);
		for (Apple& apple : apples)
			apple.init(appleTexture);
	}

	void Game::initBarriers()
	{
		barriers.resize(NUM_BARRIERS);
		for (Barrier& barrier : barriers)
			barrier.init(barrierTexture);
	}

	void Game::resetState()
	{
		randomizeApplesCount();

		player.init(playerTexture);
		initApples();
		initBarriers();
		scoreboard.init();

		numEatenApples = 0;
		isPaused = false;
		pauseTimeLeft = 0.f;
	}

	void Game::restart(bool isWin)
	{
		if (isWin)
			winSound.play();
		else
			deathSound.play();
			
		resetState();

		isPaused = true;
		pauseTimeLeft = pauseTime;
	}

	void Game::randomizeApplesCount()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dist(MIN_APPLES_COUNT, MAX_APPLES_COUNT);
		currentApplesCount = dist(gen);
	}

	bool Game::isInfiniteApplesMode() const
	{
		return hasFlag(currentMode, GameMode::InfiniteApples);
	}

	bool Game::isWithAccelerationMode() const
	{
		return hasFlag(currentMode, GameMode::WithAcceleration);
	}

} // namespace ApplesGame
