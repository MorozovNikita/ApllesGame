#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{

	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		void init(const sf::Texture& texture);
		void draw(sf::RenderWindow& window);
		void updateSprite(float dt);

		Position2D m_position;
		float m_speed{ INITIAL_SPEED };
		PlayerDirection m_direction{ PlayerDirection::Right };
		sf::Sprite m_sprite;
	};

} // namespace ApplesGame