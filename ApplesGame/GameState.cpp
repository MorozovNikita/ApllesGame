#include "GameState.h"

#include "StateStack.h"
#include "GameResources.h"
#include "Constants.h"
#include "LeaderboardBase.h"
#include "Math.h"

#include <cassert>
#include <random>
#include <memory>

namespace ApplesGame
{
    GameState::GameState(StateStack& stack, Context& context)
        : State(stack, context)
        , m_resources(context.resources)
        , m_currentMode(context.data.selectedGameMode)
        , m_scoreboard(context.resources.m_font)
        , m_numEatenApples(0)
        , m_currentApplesCount(0)
    {
        const auto textureSize = m_resources.m_backgroundTexture.getSize();
        const float scaleX = SCREEN_WIDTH / static_cast<float>(textureSize.x);
        const float scaleY = SCREEN_HEIGHT / static_cast<float>(textureSize.y);
        m_resources.m_backgroundSprite.setScale(scaleX, scaleY);

        resetState();
    }

    void GameState::draw()
    {
        mContext.window.draw(m_resources.m_backgroundSprite);

        m_player.draw(mContext.window);

        for (auto& apple : m_apples)
            apple.draw(mContext.window);

        for (auto& barrier : m_barriers)
            barrier.draw(mContext.window);

        m_scoreboard.draw(mContext.window);
    }

    bool GameState::update(sf::Time dt)
    {
        if (m_isDead)
            return false;

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
            m_player.m_position.x += m_player.m_speed * dt.asSeconds();
            break;
        case PlayerDirection::Up:
            m_player.m_position.y -= m_player.m_speed * dt.asSeconds();
            break;
        case PlayerDirection::Left:
            m_player.m_position.x -= m_player.m_speed * dt.asSeconds();
            break;
        case PlayerDirection::Down:
            m_player.m_position.y += m_player.m_speed * dt.asSeconds();
            break;
        default:
            break;
        }

        m_player.updateSprite(dt.asSeconds());

        if (m_player.m_position.x - PLAYER_SIZE / 2.f < 0.f || m_player.m_position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH
            || m_player.m_position.y - PLAYER_SIZE / 2.f < 0.f || m_player.m_position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
        {
            restart(false);
            return false;
        }

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
                    apple.m_isEaten = true;
                    apple.m_position = { -100.f, -100.f };
                    m_scoreboard.update(m_numEatenApples, m_currentApplesCount);
                }

                m_resources.m_eatAppleSound.play();
            }
        }

        if (!isInfiniteApplesMode() && m_numEatenApples >= static_cast<int>(m_apples.size()))
        {
            restart(true);
            return false;
        }

        for (int i = 0; i < NUM_BARRIERS; ++i)
        {
            if (isRectanglesCollide(m_player.m_position, { PLAYER_SIZE, PLAYER_SIZE }, m_barriers[i].m_position, { BARRIER_SIZE, BARRIER_SIZE }))
            {
                restart(false);
                return false;
            }
        }

        return true;
    }

    bool GameState::handleEvent(const sf::Event& event)
    {
        if (m_isDead)
            return false;

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape ||
                event.key.code == sf::Keyboard::P ||
                event.key.code == sf::Keyboard::Space)
            {
                mStack.pushState(States::Pause);
                return false;
            }
        }

        return true;
    }

    void GameState::initApples()
    {
        m_apples.clear();
        m_apples.reserve(m_currentApplesCount);
        for (int i = 0; i < m_currentApplesCount; ++i)
            m_apples.emplace_back(m_resources.m_appleTexture);
    }

    void GameState::initBarriers()
    {
        m_barriers.clear();
        m_barriers.reserve(NUM_BARRIERS);
        for (int i = 0; i < NUM_BARRIERS; ++i)
            m_barriers.emplace_back(m_resources.m_barrierTexture);
    }

    void GameState::resetState()
    {
        randomizeApplesCount();

        m_player.init(m_resources.m_playerTexture);
        initApples();
        initBarriers();
        m_scoreboard.reset((isInfiniteApplesMode() ? 0 : m_currentApplesCount));

        m_numEatenApples = 0;
    }

    void GameState::restart(bool isWin)
    {
        m_isDead = true;

        if (isWin)
            m_resources.m_winSound.play();
        else
            m_resources.m_deathSound.play();

        mContext.data.showGameOver = true;

        if (mContext.leaderboard.getScoreMinValue() < m_numEatenApples)
        {
            mContext.data.currentScore = m_numEatenApples;
            mStack.pushState(States::NameInput);
        }
        else
        {
            mStack.pushState(States::Leaderboard);
        }
    }

    void GameState::randomizeApplesCount()
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

    bool GameState::isInfiniteApplesMode() const
    {
        return hasFlag(m_currentMode, GameMode::InfiniteApples);
    }

    bool GameState::isWithAccelerationMode() const
    {
        return hasFlag(m_currentMode, GameMode::WithAcceleration);
    }

} // namespace ApplesGame