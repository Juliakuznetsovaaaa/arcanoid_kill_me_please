#pragma once
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Bonus {
protected:
    sf::Clock timer;

public:
    virtual void applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) = 0;
    virtual bool isExpired() = 0;
};

class PaddleWidthBonus : public Bonus {
private:
    sf::RectangleShape& paddle;
    float originalWidth;
    float bonusDuration;

public:
    PaddleWidthBonus(sf::RectangleShape& paddle, float bonusDuration)
        : paddle(paddle), bonusDuration(bonusDuration) {
        originalWidth = paddle.getSize().x;
    }

    void applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) override;

    bool isExpired() override {
        return timer.getElapsedTime().asSeconds() >= bonusDuration;
    }
};
class BallSpeedBonus : public Bonus {
private:
    sf::Vector2f& ballVelocity;
    float bonusMultiplier;
    float bonusDuration;

public:
    BallSpeedBonus(sf::Vector2f& ballVelocity, float bonusMultiplier, float bonusDuration)
        : ballVelocity(ballVelocity), bonusMultiplier(bonusMultiplier), bonusDuration(bonusDuration) {}

    void applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) override {
        // Customize the bonus effect here, such as increasing the ball speed
        ballVelocity *= bonusMultiplier;
        timer.restart();
    }

    bool isExpired() override {
        return timer.getElapsedTime().asSeconds() >= bonusDuration;
    }
};

class ExtraLifeBonus : public Bonus {

public:
    bool& isSecondLife;
    ExtraLifeBonus(bool& isSecondLife)
        : isSecondLife(isSecondLife) {}

    void applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) override {
        // Customize the bonus effect here, such as giving the player an extra life
        isSecondLife = true;
        timer.restart();
    }

    bool isExpired() override {
        return timer.getElapsedTime().asSeconds() >= 0; // This bonus doesn't expire
    }
};

class ChangeDirectionBonus : public Bonus {
public:
    sf::Vector2f& ballVelocity;
    ChangeDirectionBonus(sf::Vector2f& ballVelocity)
        : ballVelocity(ballVelocity) {}

    void applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) override {
        // Customize the bonus effect here, such as changing the ball's direction
        ballVelocity.y = -ballVelocity.y;
        timer.restart();
    }

    bool isExpired() override {
        return timer.getElapsedTime().asSeconds() >= 0; // This bonus doesn't expire
    }
};


// Implement the PaddleWidthBonus class

//class Bonus {
//public:
//	sf::CircleShape bonusBall;
//	Bonus(float posX, float posY);
//	sf::CircleShape getCircleShape() { bonusBall.move(0, 0.5);  return bonusBall; }
//	sf::CircleShape getCirclOnlyeShape() { return bonusBall; }
//	virtual ~Bonus() = default;
//	virtual void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharactery) = 0;
//};
//
//class BallSpeed : public Bonus {
//public:
//	BallSpeed(float posX, float posY) : Bonus(posX, posY) {}
//	~BallSpeed() {};
//	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override; // ïåðåîïðåäåëåíèå ôóíêöèè-÷ëåíà active() ñ àðãóìåíòîì Vector2f
//
//};
//class PaddelWidth : public Bonus {
//public:
//	sf::CircleShape bonusBall;
//	PaddelWidth(float posX, float posY) : Bonus(posX, posY) {};
//	sf::CircleShape getCircleShape() { return bonusBall; }
//	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override;
//};
//class ExtraLife : public Bonus {
//public:
//	sf::CircleShape bonusBall;
//	ExtraLife(float posX, float posY) : Bonus(posX, posY) {};
//	sf::CircleShape getCircleShape() { return bonusBall; }
//	void active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter) override;
//};