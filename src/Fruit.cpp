#include "Snake.h"
#include "Fruit.h"

void Fruit::resetRandomPosWithoutCollision(int maxX, int maxY, const Snake *snake) {
	srand(time(0));
	do
	{
		_x = rand() % maxX + 1;
		_y = rand() % maxY + 1;
	} while (collidesWithAnySnake(snake));
}

bool Fruit::collidesWithAnySnake(const Snake *snake) const
{
	for (const auto& part : snake->getBody())
	{
		if (_x == part.x && _y == part.y)
			return true;
	}

	return false;
}