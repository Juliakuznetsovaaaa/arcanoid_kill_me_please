#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>

class Field {
protected:
	float width, height, offset;
	int blocksInRow, blocksInCol;
	sf::Color colorArray[4]{ sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue };

public:
	std::vector<sf::RectangleShape> blocks;
	Field();
	std::vector<sf::CircleShape> lifes;
	~Field() {};
	int generateField(std::vector<sf::RectangleShape>& blocks);
	void generateLife();
	void delLife();
	float getWidth();
	float getHeight();
	int getBlockInRow();
	int getBlockInCol();
	int getHealthByColor(sf::Color color);
	bool isHealthZero(sf::RectangleShape& block);
	void setBlockType(sf::Color& blockColor, int& blockHealth);

};