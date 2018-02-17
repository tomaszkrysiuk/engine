#include "Colider.h"
#include <tuple>
#include <math.h>
#include <iostream>

Colider::Colider(std::vector<Ball>& b, int w, int h):
    balls(b),
    screenWidth(w),
    screenHeight(h)
{
}

void Colider::colide()
{
    colideWithWalls();
    colideWithEachOther();
}

void Colider::colideWithWalls()
{
    for(Ball& ball : balls)
    {
        float x, y, vX, vY;
        std::tie(x, y) = ball.position;
        std::tie(vX, vY) = ball.velociy;

        if(x < 0 + ball.radius)
        {
            x =0 + ball.radius;
            vX *= -1;
        }
        if(x > screenWidth - ball.radius)
        {
            x = screenWidth - ball.radius;
            vX *= -1;
        }
        if(y < 0 + ball.radius)
        {
            y =0 + ball.radius;
            vY *= -1;
        }
        if(y > screenHeight - ball.radius)
        {
            y = screenHeight - ball.radius;
            vY *= -1;
        }

        ball.position = std::make_tuple(x, y);
        ball.velociy = std::make_tuple(vX, vY);
    }
}

void Colider::colideWithEachOther()
{
    for(auto firstBall = balls.begin(); firstBall != balls.end(); ++firstBall)
    {
        for(auto secondBall = firstBall + 1; secondBall != balls.end(); ++secondBall)
        {
            if(colided(*firstBall, *secondBall))
            {
                applyColision(*firstBall, *secondBall);

            }

        }
    }
}

bool Colider::colided(Ball& first, Ball& second)
{
    colisionDistance = first.radius + second.radius;
    std::tie(firstX, firstY) = first.position;
    std::tie(secondX, secondY) = second.position;

    return circumscribedSquaresColide() and ballsColided();
}

bool Colider::circumscribedSquaresColide()
{
    return firstX <= secondX + colisionDistance and
           firstX >= secondX - colisionDistance and
           firstY <= secondY + colisionDistance and
           firstY >= secondY - colisionDistance;
}

bool Colider::ballsColided()
{
    std::cout << "cos" << std::endl;
    xDistance = firstX - secondX;
    yDistance = firstY - secondY;
    realDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));

    return (realDistance <= colisionDistance);
}

void Colider::applyColision(Ball& firstBall, Ball& secondBall)
{
    firstBall.velociy = std::make_tuple(0.0, 0.0);
    secondBall.velociy = std::make_tuple(0.0, 0.0);
}


