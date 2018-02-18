#include "Colider.h"
#include <tuple>
#include <math.h>
#include <iostream>
#include <cmath>

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
    float wallBounceFactor = -1.0;
    for(Ball& ball : balls)
    {
        float x, y, vX, vY;
        std::tie(x, y) = ball.position;
        std::tie(vX, vY) = ball.velociy;

        if(x < 0 + ball.radius)
        {
            x =0 + ball.radius;
            vX *= wallBounceFactor;
        }
        if(x > screenWidth - ball.radius)
        {
            x = screenWidth - ball.radius;
            vX *= wallBounceFactor;
        }
        if(y < 0 + ball.radius)
        {
            y =0 + ball.radius;
            vY *= wallBounceFactor;
        }
        if(y > screenHeight - ball.radius)
        {
            y = screenHeight - ball.radius;
            vY *= wallBounceFactor;
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
    distanceX = firstX - secondX;
    distanceY = firstY - secondY;
    realDistance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

    return (realDistance <= colisionDistance);
}

void Colider::applyColision(Ball& firstBall, Ball& secondBall)
{
    separate(firstBall, secondBall);
    setVelocitiesAfterColision(firstBall, secondBall);
}

void Colider::separate(Ball& firstBall, Ball& secondBall)
{
    if(realDistance <= colisionDistance)
    {
        if(realDistance != 0)
        {
            float distanceRatio = colisionDistance / realDistance;
            distanceX *= distanceRatio;
            distanceY *= distanceRatio;
            firstX =  secondX + distanceX;
            firstY =  secondY + distanceY;
        }
        else if (realDistance == 0)
        {
            firstX = secondX + colisionDistance/2;
            secondX = firstX - colisionDistance;
        }
        realDistance = colisionDistance;
        firstBall.setPosition(firstX, firstY);
        secondBall.setPosition(secondX, secondY);
    }

}

void Colider::setVelocitiesAfterColision(Ball& firstBall, Ball& secondBall)
{
    Velocity firstVelocity = firstBall.getVelocity();
    Velocity secondVelocity = secondBall.getVelocity();

    float normalizedDistanceX = distanceX / realDistance;
    float normalizedDistanceY = distanceY / realDistance;

    auto firstDot = dot({firstVelocity - secondVelocity}, {normalizedDistanceX, normalizedDistanceY});
    auto secondDot = dot({secondVelocity - firstVelocity}, {-normalizedDistanceX, -normalizedDistanceY });

    float firstMass = firstBall.mass;
    float secondMass = secondBall.mass;

    float firstMassMultipier = 2.0 * secondMass / (firstMass + secondMass);
    float secondMassMultipier = 2.0 * firstMass / (firstMass + secondMass);

    firstVelocity = firstVelocity - Velocity{firstDot * normalizedDistanceX * firstMassMultipier,
                                             firstDot * normalizedDistanceY * firstMassMultipier};
    secondVelocity = secondVelocity - Velocity{secondDot * -normalizedDistanceX * secondMassMultipier,
                                               secondDot * -normalizedDistanceY * secondMassMultipier};

    firstBall.setVelocity(firstVelocity);
    secondBall.setVelocity(secondVelocity);
}

float Colider::dot(const std::tuple<float, float>& lhs, const std::tuple<float, float>& rhs)
{
    float lhsX, lhsY, rhsX, rhsY;
    std::tie(lhsX, lhsY) = lhs;
    std::tie(rhsX, rhsY) = rhs;
    return lhsX * rhsX + lhsY * rhsY;
}
