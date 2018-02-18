#include "PerfectyElasticColider.h"

void PerfectlyElasticColider::setVelocitiesAfterColision(Ball& firstBall, Ball& secondBall)
{
    Velocity firstVelocity = firstBall.getVelocity();
    Velocity secondVelocity = secondBall.getVelocity();

    float firstMass = firstBall.mass;
    float secondMass = secondBall.mass;

    Velocity finalVelocity = (firstMass * firstVelocity + secondMass * secondVelocity)/(firstMass + secondMass);

    firstBall.setVelocity(finalVelocity);
    secondBall.setVelocity(finalVelocity);
}

void PerfectlyElasticColider::colideWithWalls()
{
    for(Ball& ball : balls)
    {
        float x, y;
        std::tie(x, y) = ball.position;

        if(x < 0 )
        {
            x += screenWidth;
        }
        if(x > screenWidth)
        {
            x -= screenWidth;
        }
        if(y < 0 )
        {
            y += screenHeight;
        }
        if(y > screenHeight)
        {
            y -= screenHeight;
        }

        ball.position = std::make_tuple(x, y);
    }
}
