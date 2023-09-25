#pragma once
#include "Paddle.h"
#include "Source.cpp"

Paddle::Paddle()
{
	width = PADDLE_WIDTH;
	height = PADDLE_HEIGHT;
	shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	x = PADDLE_POS_X;
	y = PADDLE_POS_Y;
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(x, y);

}

float Paddle::GetHeight(void)
{
	return height;
}

float Paddle::GetWidth(void)
{
	return width;
}

float Paddle::GetPosX(void)
{
	return x;
}

float Paddle::GetPosY(void)
{
	return y;
}

