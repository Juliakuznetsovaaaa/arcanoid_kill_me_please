#include "Field.h"
#include "Source.cpp"
#include <iostream>
#include "Game.h"

#define CHANCE 4

Field::Field()
{

	generateField(blocks);
}

int Field::generateField(std::vector<sf::RectangleShape>& blocks)
{
	int zeroLifeBlocks = 0;
	float posX = 0, posY = 0;

	sf::Color blockColor;
	int blockHealth = 1;

	for (auto i = 0; i < BLOCKS_IN_COL; i++)
		for (auto j = 0; j < BLOCKS_IN_ROW; j++) {
			if ((i + j) % 2 == 0) {
				continue;
			}
			posX = j * BLOCK_SIDE;
			posY = i * BLOCK_SIDE + BLOCK_SIDE;
			setBlockType(blockColor, blockHealth);
			sf::RectangleShape shape;
			if (blockColor == sf::Color::Green) {
				zeroLifeBlocks += 1;
			}
			shape.setSize(sf::Vector2f(BLOCK_SIDE, BLOCK_SIDE));
			shape.setFillColor(blockColor);
			shape.setPosition(posX, posY);
			shape.setOutlineThickness((BLOCK_SIDE) / -(BLOCK_SIDE - 10));
			shape.setOutlineColor(sf::Color::Black);
			Block newBlock(BLOCK_SIDE, BLOCK_SIDE, posX, posY, blockHealth, blockColor);
			blocks.push_back(shape);
		}
	return zeroLifeBlocks;
}
void Field::generateLife() {
	float radius = 20;
	for (auto i = 0; i < 3; i++) {
		sf::CircleShape life;
		life.setRadius(radius);
		life.setPosition(i * 3 * radius, radius * 0.25);
		life.setFillColor(sf::Color::White);
		lifes.push_back(life);
	}
}
void Field::delLife()
{
	lifes.pop_back();
}
float Field::getWidth()
{
	return width;
}

float Field::getHeight()
{
	return height;
}

int Field::getBlockInRow()
{
	return blocksInRow;
}

int Field::getBlockInCol()
{
	return blocksInCol;
}
int Field::getHealthByColor(sf::Color color)
{
	if (color == colorArray[0]) {
		return -1;
	}
	else if (color == colorArray[1]) {
		return 1;
	}
	else if (color == colorArray[2]) {
		return 2;
	}
	else if (color == colorArray[3]) {
		return 3;
	}
	else {
		return 100;
	}

}

bool Field::isHealthZero(sf::RectangleShape& block)
{
	int health = getHealthByColor(block.getFillColor());
	//std::cout << "block get health " << health << std::endl;
	if (health < 0) {
		return false;
	}
	if (health > 1) {
		block.setFillColor(colorArray[health - 1]);
		return false;
	}
	return true;
}

void Field::setBlockType(sf::Color& blockColor, int& blockHealth)
{

	switch (rand() % CHANCE) {
	case 0:
		blockColor = colorArray[0];
		blockHealth = 3;
		break;
	case 1:
		blockColor = colorArray[1];
		blockHealth = 2;
		break;
	case 2:
		blockColor = colorArray[2];
		blockHealth = 1;
		break;
	default:
		blockColor = colorArray[3];
		blockHealth = -1;
	}
}

