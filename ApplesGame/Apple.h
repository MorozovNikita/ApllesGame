#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Apple
	{
		Apple(const sf::Texture& texture);
		~Apple() = default;

		void draw(sf::RenderWindow& window);

		bool m_isEaten{ false };
		Position2D m_position;
		sf::Sprite m_sprite;
	};

} // namespace ApplesGame