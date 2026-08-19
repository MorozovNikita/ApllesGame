#include "Apple.h"

#include "Constants.h"

namespace ApplesGame
{

	void Apple::init(const sf::Texture& texture)
	{
		isEaten = false;

		position = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		sprite.setTexture(texture);
		setSpriteSize(sprite, APPLE_SIZE, APPLE_SIZE);
		setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
	}

	void Apple::draw(sf::RenderWindow& window)
	{
		sprite.setPosition(position.x, position.y);
		window.draw(sprite);
	}

} // namespace ApplesGame