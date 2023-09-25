#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Paddle.h"


class Ball {
protected:
	float radius;
	float speedX, speedY;

	float x, y;

public:
	sf::CircleShape shape;
	bool isStart = false;
	Ball();
	~Ball() {};
	float getRadius();
	float getX();
	float getY();
	float getSpeedX();
	float getSpeedY();
};