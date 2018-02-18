#pragma once
#include "Colider.h"

class NonElasticColider :
public Colider
{
    using Colider::Colider;

protected :
    void colideWithWalls() override;
    void setVelocitiesAfterColision(Ball& firstBall, Ball& secondBall) override;
};
