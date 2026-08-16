#pragma once

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{

	struct Vector2D
	{
		float x{ 0 };
		float y{ 0 };
	};

	typedef Vector2D Position2D;

	struct Rectangle
	{
		Position2D position;
		Vector2D size;
	};

	struct Circle
	{
		Position2D position;
		float radius;
	};

	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2);
	bool DoShapesCollide(const Circle& circle1, const Circle& circle2);
	bool DoShapesCollide(const Rectangle& rect, const Circle& circle);

	Position2D getRandomPositionInRectangle(const Rectangle& rect);

	Position2D getRandomPosition(const float& screenWidth, const float& screenHeight);

	bool isRectanglesCollide(const Position2D& rect1Pos, const Vector2D& rect1Size,
							 const Position2D& rect2Pos, const Vector2D& rect2Size);

	bool isCirclesCollide(const Position2D& rect1Pos, const float& rect1Radius,
						  const Position2D& rect2Pos, const float& rect2Radius);

	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

} // namespace ApplesGame