#pragma once
#include <memory>

#include "Fruit.h"
#include "CameraShaker.h"

class GameManager {
private:
    int _score;
    int _gridSize;
    bool _paused;
    bool _gameOver;
    int _gameSpeed;
    Fruit _fruit;
    std::shared_ptr<CameraShaker> _cameraShaker;

    static GameManager* _instance;

    GameManager();
    void minusGameSpeed();

public:
    static GameManager& getInstance();

    int getScore() const;
    void setScore(int newScore);
    void addScore(int points);

    int getGridSize() const;
    void setGridSize(int newGridSize);

    bool isPaused() const;
    void setPaused(bool isPaused);

    bool isGameOver() const;
    void setGameOver(bool isGameOver);

    int getGameSpeed() const;
    void setGameSpeed(int val);

    Fruit& getFruit();
    std::shared_ptr<CameraShaker> getCameraShaker();
};