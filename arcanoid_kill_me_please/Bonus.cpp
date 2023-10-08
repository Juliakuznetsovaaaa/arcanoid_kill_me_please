#include "Bonus.h"

void PaddleWidthBonus::applyBonus(sf::RectangleShape& shape, sf::Vector2f& velocity) {
       paddle.setSize(sf::Vector2f(originalWidth * 2, paddle.getSize().y)); // Удваиваем ширину ракетки
       timer.restart(); // Сбрасываем таймер длительности бонуса
   }
