#pragma once
#include "Ball.h"
#include <vector>

class Colider
{
public:
    Colider(std::vector<Ball>& balls, int screenWidth, int screenHeight);
    void colide();

private:
    void colideWithWalls();
    void colideWithEachOther();
    bool colided(Ball& first, Ball& second);
    bool circumscribedSquaresColide();
    bool ballsColided();
    void applyColision(Ball& firstBall, Ball& secondBall);

    std::vector<Ball>& balls;
    int screenWidth;
    int screenHeight;

    float colisionDistance;
    float realDistance;
    float firstX;
    float firstY;
    float secondX;
    float secondY;
    float xDistance;
    float yDistance;
};
