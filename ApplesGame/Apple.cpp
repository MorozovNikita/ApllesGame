#include "Apple.h"

#include "Constants.h"

namespace ApplesGame
{

	Apple::Apple(const sf::Texture& texture)
	{
		m_isEaten = false;

		m_position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		m_sprite.setTexture(texture);
		setSpriteSize(m_sprite, APPLE_SIZE, APPLE_SIZE);
		setSpriteRelativeOrigin(m_sprite, 0.5f, 0.5f);
	}

	void Apple::draw(sf::RenderWindow& window)
	{
		m_sprite.setPosition(m_position.x, m_position.y);
		window.draw(m_sprite);
	}

} // namespace ApplesGame