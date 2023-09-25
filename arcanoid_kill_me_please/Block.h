#pragma once
#include <SFML/Graphics.hpp>

class Block {
protected:
	float height, width;
	float x, y;
	int health;
	sf::Color color;

public:
	Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockcolor);
	~Block(void) {}
	void updateHealth(int new_health);
	float getHeight();
	float getWidth();
	float getPosX();
	float getPosY();
	sf::Color getColor();
};
