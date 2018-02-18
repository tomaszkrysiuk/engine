#pragma once
#include "Colider.h"

class PerfectlyElasticColider :
public Colider
{
    using Colider::Colider;

protected :
    void colideWithWalls() override;
    void setVelocitiesAfterColision(Ball& firstBall, Ball& secondBall) override;
};
