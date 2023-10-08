#pragma once
//
#include "Game.h"
#include <iostream>
#include "Source.cpp"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;


bool paddledAndBallCollisin(Paddle paddle, sf::CircleShape ball) {
	if (ball.getPosition().x >= paddle.shape.getPosition().x - BALL_RADIUS && ball.getPosition().x <= paddle.shape.getPosition().x + paddle.shape.getSize().x + BALL_RADIUS && ball.getPosition().y >= PADDLE_POS_Y - BALL_RADIUS && ball.getPosition().y <= PADDLE_POS_Y - 0.5 * BALL_RADIUS) {
		return true;
	}
	else {
		return false;
	}
}
void bonusActive(Bonus* bonus, sf::RectangleShape& shape, sf::Vector2f& velocity) {
	// Call the applyBonus method through the base class pointer
	bonus->applyBonus(shape, velocity);
}

void processBonusCollision(Bonus* bonus, Paddle& paddle) {
       // Обрабатываем столкновение бонусного шарика с ракеткой
       //if (bonus->shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds())) {
       //    // Активируем бонус
       //    bonus->activate(paddle);
       //}
   }

void updateBonuses(std::vector<Bonus*>& bonuses, sf::RectangleShape& shape, sf::Vector2f& velocity,
	bool& isSecondLife, sf::Vector2f& ballVelocity) {
	for (auto it = bonuses.begin(); it != bonuses.end();) {
		Bonus* bonus = *it;
		if (bonus->isExpired()) {
			delete bonus;
			it = bonuses.erase(it);
		}
		else {
			bonus->applyBonus(shape, velocity);
			std::cout << "bonus active";
			if (typeid(*bonus) == typeid(ExtraLifeBonus)) {
				ExtraLifeBonus* extraLifeBonus = dynamic_cast<ExtraLifeBonus*>(bonus);
				extraLifeBonus->isSecondLife = isSecondLife;
			}
			else if (typeid(*bonus) == typeid(ChangeDirectionBonus)) {
				ChangeDirectionBonus* changeDirectionBonus = dynamic_cast<ChangeDirectionBonus*>(bonus);
				changeDirectionBonus->ballVelocity = ballVelocity;
			}
			++it;
		}
	}
}

void movePaddleAndBall(int& p, sf::Vector2f& paddleCoordinates, Paddle& paddle, Ball& ball, int windowWidth, float& paddelCurrentWeigth, std::vector<Bonus*>& bonuses, sf::RectangleShape& shape, sf::Vector2f& velocity){	double spinBall = SPEED + 0.2;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		if (paddleCoordinates.x < WINDOW_WEIDH - paddelCurrentWeigth) {
			paddle.shape.move(spinBall, 0);
			if (p == 0)
				ball.shape.move(spinBall, 0);
		}

	if (Keyboard::isKeyPressed(Keyboard::Left))
		if (paddleCoordinates.x > 0) {
			paddle.shape.move(-spinBall, 0);
			if (p == 0)
				ball.shape.move(-spinBall, 0);
		}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		p = 1;
		for (const auto& bonus : bonuses) {
			bonusActive(bonus, paddle.shape, velocity);
		}
	}
}

void moveBall(Ball& ball, Paddle& paddle, sf::Vector2f& velocity, int& p, std::vector<Bonus*>& bonuses) {
	if (ball.shape.getPosition().x < 0 || ball.shape.getPosition().x>WINDOW_WEIDH - BALL_RADIUS) {
		velocity.x = -velocity.x;
	}
	if (ball.shape.getPosition().y < 50) {
		velocity.y = -velocity.y;
	}
	if (paddledAndBallCollisin(paddle, ball.shape)) {

		velocity.y = -velocity.y;
	}
	for (auto it = bonusBalls.begin(); it != bonusBalls.end();) {
        if (ball.shape.getGlobalBounds().intersects(it->getGlobalBounds())) {
            // Активация бонуса
            // ... выполнение специфичных действий для бонуса ...
            // Удаление бонусного шарика
            it = bonusBalls.erase(it);
        }
        else {
            ++it;
        }
    }
}

	


void processBonusesCollisionWithPaddle(Paddle& paddle, std::vector<Bonus*>& bonuses) {
       for (auto it = bonuses.begin(); it != bonuses.end();) {
           Bonus* bonus = *it;
           processBonusCollision(bonus, paddle);
           if (bonus->isExpired()) {
               delete bonus;
               it = bonuses.erase(it);
           } else {
               ++it;
           }
       }
   }

bool delLife(Text& text, sf::Vector2f& ballCoordinates, Paddle& paddle, sf::Vector2f& velocity, Ball& ball, int& p, int& l, bool& isSpeedChange, bool& isPaddleChange, bool& isSecondLife, bool& isDiffrentDirection, sf::RectangleShape& extralife, int& score, std::vector<Bonus*>& bonuses) {	
	if (ballCoordinates.y > WINDOW_HEIGHT - 10) {
		p = 0;
		if (isSpeedChange) {
			velocity.y = -SPEED;
			velocity.x = -SPEED;
			isSpeedChange = false;
		}

		ball.shape.setPosition(BALL_POS_X, BALL_POS_Y);
		paddle.shape.setPosition(paddle.getX(), paddle.getY());
		paddle.shape.setSize(sf::Vector2f(PADDLE_WIDTH - (l+1) * 10, PADDLE_HEIGHT));
		if (isSecondLife) {
			if (isPaddleChange) {
				paddle.shape.setSize(sf::Vector2f(PADDLE_WIDTH - (l+1) * 10 + 10, PADDLE_HEIGHT));
				isPaddleChange = false;
			}
			extralife.setFillColor(sf::Color::Transparent);
			isSecondLife = false;
			
			for (const auto& bonus : bonuses) {
				bonusActive(bonus, paddle.shape, velocity);
			}
			return false;
		}

		isDiffrentDirection = false;
		l++;
		if (l == 3) {

			ball.shape.setFillColor(Color::Transparent);
			paddle.shape.setFillColor(Color::Transparent);
		}

		return true;
	}
	return false;

}

void delBlock(int& score, Text& text, Field& field, Ball& ball, std::vector<RectangleShape>& bricks, Vector2f& ballCoordinates, Vector2f& velocity, std::vector<Bonus*>& bonuses, Paddle& paddle, int& deletedBlocks) {
	std::vector<bool> isFilled(bricks.size(), false);
	sf::FloatRect ballBounds = ball.shape.getGlobalBounds();
	ballBounds.left -= 4;
	ballBounds.top -= 4;
	ballBounds.width += 4;
	ballBounds.height += 4;
	float angle = 0.1;
	for (unsigned k = 0; k < bricks.size(); k++) {
		if (ballBounds.intersects(bricks[k].getGlobalBounds()) && isFilled[k] != true) {
			isFilled[k] = true;
			
			float angle = std::atan2(velocity.y, velocity.x);
			angle += (rand() % 21 -1) * M_PI / 180;
			velocity.y = std::sin(angle) * std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
			velocity = sf::Vector2f(-velocity.x, -velocity.y);
			if (field.isHealthZero(bricks[k])) {
				deletedBlocks++;
				score++;
				text.setString("Score: " + std::to_string(score));
				
				bricks[k].setPosition(2000, 2000);
			}
			break;
		}
	}
}



Game::Game()
{
	score = 0;

	deletedBlocks = field.generateField(field.blocks);
}
int Game::start() {

	setlocale(LC_ALL, "Russian");

	unsigned int windowWidth = WINDOW_WEIDH, windowHeight = WINDOW_HEIGHT;
	std::vector<sf::RectangleShape> bricks;
	std::vector<sf::CircleShape> bonusBalls;
	int l = 0; int p = 0;  int count = 0;
	int score = 0;
	float paddelCurrentWeigth = PADDLE_WIDTH;
	Vector2f velocity(-SPEED, -SPEED);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WEIDH, WINDOW_HEIGHT), "Arcanoid");
	Paddle paddle;
	std::vector<Bonus*> bonuses;

	sf::RectangleShape extralife;
	Vector2f extraLifeSize(WINDOW_WEIDH, 5);
	extralife.setPosition(0, WINDOW_HEIGHT - 50);
	extralife.setSize(extraLifeSize);
	extralife.setFillColor(sf::Color::Transparent);

	bool isPaddleChange = false;
	bool isSpeedChange = false;
	bool isSecondLife = false;
	bool isDiffrentDirection = false;

	std::vector<sf::CircleShape> bonusBalls;

	Font font;
	font.loadFromFile("ArialRegular.ttf");
	Text text;
	text.setFont(font);
	text.setString("Score: " + std::to_string(score));
	text.setCharacterSize(24);
	text.setPosition(WINDOW_WEIDH - 150, 10);
	text.setFillColor(Color::White);
	text.setString("Score: " + std::to_string(score));

	Ball ball;
	Field field;

	field.generateLife();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (isDiffrentDirection && rand() % 3 == 0) {
			velocity.y = -velocity.y;
			velocity.x = -velocity.x;
			isDiffrentDirection = false;
			for (const auto& bonus : bonuses) {
				bonusActive(bonus, paddle.shape, velocity);
			}
		}
		Vector2f m = paddle.shape.getPosition();
		if (deletedBlocks != BLOCKS_NUM) {
			movePaddleAndBall(p, m, paddle, ball, windowWidth, paddelCurrentWeigth, bonuses, paddle.shape, velocity);
		}
		else {
			p = 0;
		}
		if (p == 1 && l != 3) {

			ball.shape.move(velocity);
			Vector2f b = ball.shape.getPosition();
			moveBall(ball, paddle, velocity, p, bonuses);
			if (delLife(text, b, paddle, velocity, ball, p, l, isSpeedChange, isPaddleChange, isSecondLife, isDiffrentDirection, extralife, score, bonuses)) {

				field.delLife();
			}
			delBlock(score, text, field, ball, field.blocks, b, velocity, bonuses, paddle, deletedBlocks);
			sf::Vector2f pddleSize = paddle.shape.getSize();
			updateBonuses(bonuses, paddle.shape, pddleSize, isSecondLife, velocity);
		}

		window.clear();

		for (auto& brick : field.blocks) window.draw(brick);
		for (auto& life : field.lifes) window.draw(life);
		for (auto& bonusBall : bonusBalls) {
           widow.draw(bonusBall);
        }
		window.draw(text);
		window.draw(paddle.shape);
		window.draw(ball.shape);
		window.draw(extralife);

		window.display();
	}
	return 0;
}
