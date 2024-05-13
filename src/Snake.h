#pragma once
#include <deque>
#include <vector>
#include <iostream>
#include "GameManager.h"

extern enum Direction { UP, DOWN, LEFT, RIGHT };

struct BodyPart { int x, y; };

class Snake {
public:
    Snake(int x, int y, int length = 4, int initialDirection = RIGHT)
        : _direction(initialDirection),
        _gameManager(&GameManager::getInstance())
    {
        _fruit = &_gameManager->getFruit();
        _gridSize = _gameManager->getGridSize();

        for (int i = 0; i < length; ++i) 
        {
            _body.push_back({ x - i, y });
        }

    }

    void init(int x, int y, int length = 4, int initialDirection = RIGHT)
    {
        _body.clear();
        _direction = initialDirection;

        for (int i = 0; i < length; ++i)
        {
            _body.push_back({ x - i, y });
        }
    }

    void move() 
    {
        bool grow = false;
        int delX = 0;
        int delY = 0;

        switch (_direction) 
        {
            case UP:
                delY = 1;
                break;
            case DOWN:
                delY = -1;
                break;
            case LEFT:
                delX = -1;
                break;
            case RIGHT:
                delX = 1;
                break;
        }

        int headX = _body.front().x + delX;
        int headY = _body.front().y + delY;

        if (headX == _fruit->x() && headY == _fruit->y()) {
            grow = true;
            _gameManager->addScore(1);
            _fruit->resetRandomPosWithoutCollision(19, 19, this);
        }

        if (headX > _gridSize ||
            headY > _gridSize ||
            headX <= 0 ||
            headY <= 0)
        {
            _gameManager->setPaused(true);
            _gameManager->setGameOver(true);
        }

        if (collidesWithBody(headX, headY))
        {
            _gameManager->setPaused(true);
            _gameManager->setGameOver(true);
        }

        
        
        _body.push_front({ headX, headY });

        if (!grow)
            _body.pop_back();
    }

    void setDirection(int newDirection) 
    {
        if ((newDirection == UP && _direction != DOWN) ||
            (newDirection == DOWN && _direction != UP) ||
            (newDirection == LEFT && _direction != RIGHT) ||
            (newDirection == RIGHT && _direction != LEFT)) 
        {
            _direction = newDirection;
        }
    }

    const std::deque<BodyPart>& getBody() const
    {
        return _body;
    }

private:

    GameManager* _gameManager;
    Fruit* _fruit;
    std::deque<BodyPart> _body;
    int _direction;
    //int _headX, _headY;
    int _gridSize;

    bool collidesWithBody(int x, int y) const
    {
        for (const auto& part : _body)
        {
            if (x == part.x && y == part.y)
                return true;
        }

        return false;
    }
};
