#pragma once

#include <vector>
#include "Renderer.h"
#include "Ball.h"
#include "Colider.h"

class Bounce
{
public:
    Bounce(Renderer& renderer, int screenWidth, int screenHeight);

    void start();

private:
    void handleEvents();
    void addBlackBall();
    void addWhiteBall();
    void addRedBall();
    void drawLine();
    void drawBalls();
    void applyColisions();
    void drawAndPresent();
    void applyGravity(float g);
    void destroyIfNeeded();
    void makeSnow(int count);
    int getZ();

    int xStart = 0;
    int xStop = 0;
    int yStart = 0;
    int yStop = 0;
    bool shouldDrawLine = false;
    bool quit = false;
    bool restart = false;
    int screenWidth;
    int screenHeight;
    Renderer& renderer;
    std::vector<Ball> balls;
};

