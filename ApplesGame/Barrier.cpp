#include "Barrier.h"

#include "Constants.h"

namespace ApplesGame
{

	void Barrier::init(const sf::Texture& texture)
	{
		position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		sprite.setTexture(texture);
		setSpriteSize(sprite, BARRIER_SIZE, BARRIER_SIZE);
		setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}

	void Barrier::draw(sf::RenderWindow& window)
	{
		sprite.setPosition(position.x, position.y);
		window.draw(sprite);
	}

} // namespace ApplesGame