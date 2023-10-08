#include "Bonus.h"



// Implement the PaddleWidthBonus class
void PaddleWidthBonus::applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) {
    velocity.x += 100;
    shape.setSize(velocity);
    timer.restart();
}
//void BallSpeed::active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter)
//{
//
//	velocity *= newCharacter;
//}
//
//Bonus::Bonus(float posX, float posY)
//{
//	bonusBall.setFillColor(sf::Color::White);
//	bonusBall.setRadius(10);
//	bonusBall.setPosition(posX, posY);
//
//
//}
//
//void PaddelWidth::active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter)
//{
//	velocity.x += newCharacter;
//	shape.setSize(velocity);
//}
//
//void ExtraLife::active(sf::RectangleShape& shape, sf::Vector2f& velocity, float newCharacter)
//{
//	shape.setFillColor(sf::Color::Red);
//}


