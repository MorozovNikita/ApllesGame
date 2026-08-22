#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Apple
	{
		void init(const sf::Texture& texture);
		void draw(sf::RenderWindow& window);

		bool m_isEaten{ false };
		Position2D m_position;
		sf::Sprite m_sprite;
	};

} // namespace ApplesGame