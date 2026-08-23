#include "Barrier.h"

#include "Constants.h"

namespace ApplesGame
{

	Barrier::Barrier(const sf::Texture& texture)
	{
		m_position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		m_sprite.setTexture(texture);
		setSpriteSize(m_sprite, BARRIER_SIZE, BARRIER_SIZE);
		setSpriteRelativeOrigin(m_sprite, 0.5f, 0.5f);
	}

	void Barrier::draw(sf::RenderWindow& window)
	{
		m_sprite.setPosition(m_position.x, m_position.y);
		window.draw(m_sprite);
	}

} // namespace ApplesGame