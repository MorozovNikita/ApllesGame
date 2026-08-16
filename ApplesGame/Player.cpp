#include "Player.h"

#include "Game.h"

namespace ApplesGame
{

	void Player::init(const sf::Texture& texture)
	{
		// init player state
		position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		speed = INITIAL_SPEED;
		direction = PlayerDirection::Right;

		// init player sprite
		sprite.setTexture(texture);
		setSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
		setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		sprite.setRotation(0.f);
	}

	void Player::draw(sf::RenderWindow& window)
	{
		sprite.setPosition(position.x, position.y);
		window.draw(sprite);
	}

	void Player::updateSprite(float dt)
	{
		float targetAngle = 0.f;
		switch (direction)
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
		float currentAngle = sprite.getRotation();
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

		sprite.setRotation(currentAngle);
	}

} // namespace ApplesGame