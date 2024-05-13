#pragma once
#include <GL/freeglut.h>  
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

class CameraShaker {
private:
    clock_t shakeStartTime;
    bool shaking = false;
public:
    void updateCamera()
    {
        if (shaking)
        {

            clock_t currentTime = clock();
            double elapsedTime = (double)(currentTime - shakeStartTime) / CLOCKS_PER_SEC;
            double shakeDuration = 0.5;

            if (elapsedTime >= shakeDuration) {
                stopShake();
                return;
            }

            float shakeX = randomFloat(-0.3f, 0.3f);
            float shakeY = randomFloat(-0.3f, 0.3f);

            gluLookAt(shakeX, shakeY, 10.0f, shakeX, shakeY, 0, 0, 1, 0);
        }
        else
        {
            gluLookAt(0, 0, 10.0f, 0, 0, 0, 0, 1, 0);
        }
    }

    void startShake()
    {
        //std::cout << "startShake()" << std::endl;
        shaking = true;
        shakeStartTime = clock();
    }

    void stopShake()
    {
        //std::cout << "stopShake()" << std::endl;
        shaking = false;
    }

    float randomFloat(float min, float max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
};