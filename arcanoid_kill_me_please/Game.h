#pragma once
#include "Field.h"
#include "Bonus.h"
#include "Ball.h"
#include "Paddle.h"

class Game {
private:
	int score;
	sf::RenderWindow window;

public:
	Field field;
	Paddle paddle;
	Ball ball;
	int deletedBlocks = 0;
	
	enum BonusType { SpeedUp, SlowDown, ExtraLife, PaddleWidth, DiffrentDirection }; // пример возможных типов бонусов
	Game();
	~Game() {};
	int start();
};