#pragma once
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Bonus {
public:
	sf::CircleShape bonusBall;
	Bonus(float posX, float posY);
	sf::CircleShape getCircleShape() { bonusBall.move(0, 0.5);  return bonusBall; }
	sf::CircleShape getCirclOnlyeShape() { return bonusBall; }
	virtual ~Bonus() = default;
	virtual void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharactery) = 0;
};

class BallSpeed : public Bonus {
public:
	BallSpeed(float posX, float posY) : Bonus(posX, posY) {}
	~BallSpeed() {};
	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override; // ïåðåîïðåäåëåíèå ôóíêöèè-÷ëåíà active() ñ àðãóìåíòîì Vector2f

};
class PaddelWidth : public Bonus {
public:
	sf::CircleShape bonusBall;
	PaddelWidth(float posX, float posY) : Bonus(posX, posY) {};
	sf::CircleShape getCircleShape() { return bonusBall; }
	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override;
};
class ExtraLife : public Bonus {
public:
	sf::CircleShape bonusBall;
	ExtraLife(float posX, float posY) : Bonus(posX, posY) {};
	sf::CircleShape getCircleShape() { return bonusBall; }
	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override;
};