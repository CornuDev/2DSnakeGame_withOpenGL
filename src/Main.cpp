#pragma once

#include <stdio.h> 
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>



/*** freeglut***/
#include ".\GL\freeglut.h"

#include "FPSCounter.h"
#include "Fruit.h"
#include "Snake.h"
#include "GameManager.h"
#include "CameraShaker.h"
#include "UIText.h"

#define PI 3.14159265

struct Point { int x, y; };
struct Color { float r, g, b; };



/*Setting Color*/
Color wallColor { 0, 0.9, 0.9};
Color gridColor1 { 0, 0.1, 0.1};
Color gridColor2 { 0, 0.2, 0.2};
Color snakeColor{ 0.9, 0.9, 0.9};
Color fruitColor{ 1.0, 0.0, 1.0};

Color white{ 1.0, 1.0, 1.0 };
Color black{ 0.0, 0.0, 0.0 };
Color red{ 1.0, 0.0, 0.0 };
Color green{ 0.0, 1.0, 0.0 };
Color blue{ 0.0, 0.0, 1.0 };

/*Snack Game*/
GameManager* gameManager = &GameManager::getInstance();
Snake snake(5, 5);

void initGame();

/*glut func*/
void ChangeSize(int, int);
void RenderScene(void);

/*drawFunc*/
void drawGrid(int num);
void drawPoint(int x, int y, Color);
void drawBrick(int x, int y, Color);
void drawWalls(int gridSize);
void drawSnake(Snake* snake);
void drawEye(int x, int y);
void drawFruit(Fruit* fruit);

/*glut func*/
void myCleanUp();
void myTimerFunc(int value);
void myKeyboardFunc(unsigned char Key, int x, int y);
void myMouseFunc(int button, int state, int x, int y);

/*helper func*/
void setGlColor3f(const Color& c);

/*Window & Cam*/
float winSizeX = 800;
float winSizeY = 800;
float left = 0 - 5;
float right = 30 - 5;
float bottom = 0 - 5;
float top = 30 - 5;
float znear = 0 - 5;
float zfar = 30 - 5;
int px, py;

std::unique_ptr<FPSCounter> fpsCounter(new FPSCounter());

UIText scoreUI;
UIText stateUI;


void initGame()
{
    snake.init(5, 5);
    gameManager->setPaused(false);
    gameManager->setGameOver(false);
    gameManager->setScore(0);
    gameManager->setGameSpeed(100);
}

void myTimerFunc(int value)
{
    if (!gameManager->isPaused())
        snake.move();

    glutTimerFunc(gameManager->getGameSpeed(), myTimerFunc, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("2D Snake Game");

    glutKeyboardFunc(myKeyboardFunc);
    glutMouseFunc(myMouseFunc);

    initGame();

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(gameManager->getGameSpeed(), myTimerFunc, 0);
    atexit(myCleanUp);

    glutMainLoop();
    return 0;
}

void myCleanUp()
{
    delete gameManager;
}

void ChangeSize(int w, int h)
{
    printf("Window Size= %d X %d\n", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, znear, zfar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, znear, zfar);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    
    gameManager->getCameraShaker()->updateCamera();
    //gluLookAt(0, 0, 10.0f, 0, 0, 0, 0, 1, 0);
    
    drawSnake(&snake);
    drawFruit(&gameManager->getFruit());
    
    drawGrid(gameManager->getGridSize());
    drawWalls(gameManager->getGridSize() + 1);

    fpsCounter->displayAndUpdateFPS(left * 0.9, top * 0.9);

    scoreUI.display("Score: " + std::to_string(gameManager->getScore()), left * 0.9, top * 0.9 - 1);

    if (gameManager->isGameOver())
        stateUI.display("GameOver!", 8, 9);

    glutSwapBuffers();
}

void drawPoint(int x, int y, Color color) {
    {
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_QUADS);
        glVertex2f(x - 1, y - 1);
        glVertex2f(x, y - 1);
        glVertex2f(x, y);
        glVertex2f(x - 1, y);
        glEnd();
    }
}

void drawGrid(int num) {
    for (int i = 1; i <= num; i++)
    {
        for (int j = 1; j <= num; j++)
        {
            if ((i+j) % 2)
                drawPoint(i, j, gridColor1);
            else
                drawPoint(i, j, gridColor2);
        }
    }
}

void drawBrick(int x, int y, Color color) {
    {
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_QUADS);
        glVertex2f(x - 0.95, y - 0.95);
        glVertex2f(x -0.05, y - 0.95);
        glVertex2f(x - 0.05, y - 0.05);
        glVertex2f(x - 0.95, y -0.05);
        glEnd();
    }
}

void drawWalls(int gridSize)
{
    for (int i = 0; i <= gridSize; i++) {
        drawBrick(i, 0, wallColor);
        drawBrick(i, gridSize, wallColor);
        drawBrick(0, i, wallColor);
        drawBrick(gridSize, i, wallColor);
    }
}

void drawSnake(Snake* snake)
{
    std::deque<BodyPart> snakeBody = snake->getBody();
    setGlColor3f(snakeColor);
    int len = snakeBody.size();

    drawEye(snakeBody[0].x, snakeBody[0].y);

    for (int i = 0; i < len; i++)
    {
        drawPoint(snakeBody[i].x, snakeBody[i].y, snakeColor);
    }
}

void drawEye(int x, int y)
{
    setGlColor3f(gridColor1);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.5, y - 0.5);
    glVertex2f(x - 0.3, y - 0.5);
    glVertex2f(x - 0.3, y - 0.3);
    glVertex2f(x - 0.5, y - 0.3);
    glEnd();
}

void drawFruit(Fruit* fruit)
{
    int x = fruit->x();
    int y = fruit->y();

    setGlColor3f(fruitColor);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.8, y - 0.8);
    glVertex2f(x - 0.2, y - 0.8);
    glVertex2f(x - 0.2, y - 0.2);
    glVertex2f(x - 0.8, y - 0.2);
    glEnd();
}

void myKeyboardFunc(unsigned char Key, int x, int y) 
{
    switch (Key) 
    {
        case 'p':
            if (!gameManager->isGameOver())
            {
                if (!gameManager->isPaused())
                    std::cout << "pause!" << std::endl;
                else
                    std::cout << "go!" << std::endl;

                gameManager->setPaused(!gameManager->isPaused());
            }
            break;
        
        case 'b':
            std::cout << "reset!" << std::endl;
            initGame();
            break;

        case 'w':
            if(!gameManager->isPaused())
                snake.setDirection(UP);
            break;
        case 's':
            if (!gameManager->isPaused())
                snake.setDirection(DOWN);
            break;
        case 'a':
            if (!gameManager->isPaused())
                snake.setDirection(LEFT);
            break;
        case 'd':
            if (!gameManager->isPaused())
                snake.setDirection(RIGHT);
            break;
    }
}

void setGlColor3f(const Color& c) {
    glColor3f(c.r, c.g, c.b);
}

//For Testing
void myMouseFunc(int button, int state, int x, int y) {

    if (state == GLUT_DOWN) {
        //printf("Screen Coordinates: (%d, %d)\n", x, y);
        /* Screen to NDC*/
        float xn = (x - winSizeX / 2) / (winSizeX / 2);
        float yn = (winSizeY / 2 - y) / (winSizeY / 2);
        float zn = -1;
        //printf("NDC Coordinates: (%f, %f, %f)\n", xn, yn, zn);
        /* NDC to Atho*/
        float sx = (xn + 1) * (right - left) / 2 + left;
        float sy = (yn + 1) * (top - bottom) / 2 + bottom;
        float sz = -(zn + 1) * (zfar - znear) / 2 - znear;
        //printf("Space Coordinates: (%f, %f, %f)\n", sx, sy, sz);
        px = round(sx + 0.5);
        py = round(sy + 0.5);
        printf("Point : (%d, %d)\n", px, py);
    }
}

