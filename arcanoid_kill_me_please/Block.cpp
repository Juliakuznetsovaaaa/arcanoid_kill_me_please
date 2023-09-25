#include "Block.h"

Block::Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockColor)
{
	height = blockHeight;
	width = blockWidth;
	x = posX;
	y = posY;
	health = blockHealth;
	color = blockColor;
}



void Block::updateHealth(int new_health)
{
	health += new_health;
}


float Block::getHeight()
{
	return height;
}

float Block::getWidth()
{
	return width;
}

float Block::getPosX()
{
	return x;
}

float Block::getPosY()
{
	return y;
}

sf::Color Block::getColor()
{
	return color;
}



