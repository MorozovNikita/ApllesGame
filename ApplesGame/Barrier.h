#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Barrier
	{
		void init(const sf::Texture& texture);
		void draw(sf::RenderWindow& window);

		Position2D m_position;
		sf::RectangleShape m_shape;
		sf::Sprite m_sprite;
	};

} // namespace ApplesGame