#pragma once
#include <cstdlib> 
#include <ctime> 

class Snake;

class Fruit {
public:
	Fruit(int x, int y): _x(x), _y(y){ }
	int x() { return _x; };
	int y() { return _y; };

	void resetRandomPosWithoutCollision(int maxX, int maxY, const Snake *snake);
			
private:
	int _x;
	int _y;

	bool collidesWithAnySnake(const Snake *snake) const;
};
