#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Barrier
	{
		void init(const sf::Texture& texture);
		void draw(sf::RenderWindow& window);

		Position2D position;
		sf::RectangleShape shape;
		sf::Sprite sprite;
	};

} // namespace ApplesGame