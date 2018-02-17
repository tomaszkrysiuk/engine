#pragma once

#include <vector>
#include "Renderer.h"
#include "Ball.h"

class Bounce
{
public:
    Bounce(Renderer& renderer, int screenWidth, int screenHeight);

    void start();

private:
    void handleEvents();
    void addBlackBall();
    void drawLine();
    void drawBalls();

    int xStart = 0;
    int xStop = 0;
    int yStart = 0;
    int yStop = 0;
    bool shouldDrawLine = false;
    bool quit = false;
    int screenWidth;
    int screenHeight;
    Renderer& renderer;
    std::vector<Ball> balls;
};

