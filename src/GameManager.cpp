#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager() 
    : _score(0),
    _gridSize(20), 
    _paused(false), 
    _gameOver(false), 
    _gameSpeed(100), 
    _fruit(15, 15), 
    _cameraShaker(new CameraShaker()){}

GameManager& GameManager::getInstance() 
{
    if (_instance == nullptr) 
    {
        _instance = new GameManager();
    }
    return *_instance;
}

int GameManager::getScore() const 
{
    return _score;
}

void GameManager::setScore(int newScore) 
{
    _score = newScore;
}

void GameManager::addScore(int points) 
{
    _score += points;
    minusGameSpeed();
}

int GameManager::getGridSize() const 
{
    return _gridSize;
}

void GameManager::setGridSize(int newGridSize) 
{
    _gridSize = newGridSize;
}

bool GameManager::isPaused() const 
{
    return _paused;
}

void GameManager::setPaused(bool isPaused) 
{
    _paused = isPaused;
}

bool GameManager::isGameOver() const 
{
    return _gameOver;
}

void GameManager::setGameOver(bool isGameOver) 
{
    _gameOver = isGameOver;
    if (isGameOver)
        _cameraShaker->startShake();
}

int GameManager::getGameSpeed() const 
{
    return _gameSpeed;
}

void GameManager::setGameSpeed(int val)
{
    _gameSpeed = val;
}

void GameManager::minusGameSpeed() 
{
    if (_gameSpeed > 10) 
    {
        _gameSpeed -= 3;
    }
}

Fruit& GameManager::getFruit() 
{
    return _fruit;
}

std::shared_ptr<CameraShaker> GameManager::getCameraShaker()
{
    return _cameraShaker;
}