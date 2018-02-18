#pragma once
#include "Ball.h"
#include <vector>

class Colider
{
public:
    Colider(std::vector<Ball>& balls, int screenWidth, int screenHeight);
    void colide();

protected:
    virtual void colideWithWalls();
    virtual void setVelocitiesAfterColision(Ball& firstBall, Ball& secondBall);
    virtual bool colided(Ball& first, Ball& second);
    virtual void applyColision(Ball& firstBall, Ball& secondBall);

    std::vector<Ball>& balls;
    int screenWidth;
    int screenHeight;

    float colisionDistance;
    float realDistance;
    float firstX;
    float firstY;
    float secondX;
    float secondY;
    float distanceX;
    float distanceY;

private:
    void colideWithEachOther();
    bool circumscribedSquaresColide();
    bool ballsColided();
    void separate(Ball& firstBall, Ball& secondBall);
    float dot(const std::tuple<float, float>& lhs, const std::tuple<float, float>& rhs);
};
