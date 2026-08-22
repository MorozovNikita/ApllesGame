#include "Player.h"

#include "Game.h"

namespace ApplesGame
{

	void Player::init(const sf::Texture& texture)
	{
		// init player state
		m_position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		m_speed = INITIAL_SPEED;
		m_direction = PlayerDirection::Right;

		// init player sprite
		m_sprite.setTexture(texture);
		setSpriteSize(m_sprite, PLAYER_SIZE, PLAYER_SIZE);
		setSpriteRelativeOrigin(m_sprite, 0.5f, 0.5f);
		m_sprite.setRotation(0.f);
	}

	void Player::draw(sf::RenderWindow& window)
	{
		m_sprite.setPosition(m_position.x, m_position.y);
		window.draw(m_sprite);
	}

	void Player::updateSprite(float dt)
	{
		float targetAngle = 0.f;
		switch (m_direction)
		{
		case PlayerDirection::Right: 
			targetAngle = 0.f;   
			break;
		case PlayerDirection::Up:    
			targetAngle = -90.f; 
			break;
		case PlayerDirection::Left:  
			targetAngle = 180.f; 
			break;
		case PlayerDirection::Down:  
			targetAngle = 90.f;  
			break;
		}

		// smooth rotation
		float currentAngle = m_sprite.getRotation();
		float diff = targetAngle - currentAngle;

		// angle normalization
		while (diff > 180.f)  
			diff -= 360.f;
		while (diff < -180.f) 
			diff += 360.f;

		float rotationSpeed = 360.f; // degrees per second
		if (std::abs(diff) > rotationSpeed * dt)
			currentAngle += (diff > 0 ? 1 : -1) * rotationSpeed * dt;
		else
			currentAngle = targetAngle;

		m_sprite.setRotation(currentAngle);
	}

} // namespace ApplesGame