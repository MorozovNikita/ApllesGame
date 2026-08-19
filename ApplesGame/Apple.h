#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace ApplesGame
{

	struct Apple
	{
		void init(const sf::Texture& texture);
		void draw(sf::RenderWindow& window);

		bool isEaten{ false };
		Position2D position;
		sf::Sprite sprite;
	};

} // namespace ApplesGame