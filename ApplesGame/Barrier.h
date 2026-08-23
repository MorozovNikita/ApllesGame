#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Barrier
	{
		Barrier(const sf::Texture& texture);
		~Barrier() = default;

		void draw(sf::RenderWindow& window);

		Position2D m_position;
		sf::RectangleShape m_shape;
		sf::Sprite m_sprite;
	};

} // namespace ApplesGame