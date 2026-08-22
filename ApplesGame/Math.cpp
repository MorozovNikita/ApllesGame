#include "Math.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>

namespace ApplesGame
{
	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2)
	{
		return rect1.position.x < rect2.position.x + rect2.size.x
			   && rect1.position.x + rect1.size.x > rect2.position.x
			   && rect1.position.y < rect2.position.y + rect2.size.y
			   && rect1.position.y + rect1.size.y > rect2.position.y;
	}

	bool DoShapesCollide(const Circle& circle1, const Circle& circle2)
	{
		float dx = circle1.position.x - circle2.position.x;
		float dy = circle1.position.y - circle2.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < circle1.radius + circle2.radius;
	}

	bool DoShapesCollide(const Rectangle& rect, const Circle& circle)
	{
		float dx = circle.position.x - std::max(rect.position.x, std::min(circle.position.x, rect.position.x + rect.size.x));
		float dy = circle.position.y - std::max(rect.position.y, std::min(circle.position.y, rect.position.y + rect.size.y));
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}

	Position2D getRandomPositionInRectangle(const Rectangle& rect)
	{
		return { rand() / (float)RAND_MAX * rect.size.x + rect.position.x,
				 rand() / (float)RAND_MAX * rect.size.y + rect.position.y };
	}

	Position2D getRandomPosition(const float& screenWidth, const float& screenHeight)
	{
		return { rand() / (float)RAND_MAX * screenWidth,
				 rand() / (float)RAND_MAX * screenHeight };
	}

	bool isRectanglesCollide(const Position2D& rect1Pos, const Vector2D& rect1Size, const Position2D& rect2Pos, const Vector2D& rect2Size)
	{
		float dx = fabs(rect1Pos.x - rect2Pos.x);
		float dy = fabs(rect1Pos.y - rect2Pos.y);

		return dx <= (rect1Size.x + rect2Size.x) / 2.f && dy <= (rect1Size.y + rect2Size.y) / 2.f;
	}

	bool isCirclesCollide(const Position2D& rect1Pos, const float& rect1Radius, const Position2D& rect2Pos, const float& rect2Radius)
	{
		float squareDistance = (rect1Pos.x - rect2Pos.x) * (rect1Pos.x - rect2Pos.x) +
							   (rect1Pos.y - rect2Pos.y) * (rect1Pos.y - rect2Pos.y);

		float squareRadiusSum = (rect1Radius + rect2Radius) * (rect1Radius + rect2Radius);

		return squareDistance < squareRadiusSum;
	}

	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void centerTextHorizontally(sf::Text& text, float centerX, float y)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setPosition(centerX - (bounds.left + bounds.width / 2.f), y - (bounds.top + bounds.height / 2.f));
	}

} // namespace ApplesGame