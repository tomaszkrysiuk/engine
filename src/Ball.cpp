#include "Ball.h"

Ball::Ball(Coordinates position, int rad, float mass, Velocity vel, const Texture& tex):
    position(position),
    radius(rad),
    mass(mass),
    velociy(vel),
    acceleration(
{
    0.0, 0.0
}),
texture(&tex) {}

void Ball::applyForce(Force force)
{
    float fX, fY, aX, aY;
    std::tie(fX, fY) = force;
    std::tie(aX, aY) = acceleration;
    acceleration = std::make_tuple(aX + fX/mass, aY + fY/mass);
}

void Ball::applyForce(float fX, float fY)
{
    float aX, aY;
    std::tie(aX, aY) = acceleration;
    acceleration = std::make_tuple(aX + fX/mass, aY + fY/mass);
}

void Ball::applyAcceleration(Acceleration acc)
{
    acceleration = std::make_tuple(std::get<0>(acceleration) + std::get<0>(acc),
                                   std::get<1>(acceleration) + std::get<1>(acc));
}

const Coordinates& Ball::getPosition()
{
    return position;
}

void Ball::setPosition(float x, float y)
{
    position = std::make_tuple(x, y);
}

void Ball::setPosition(Coordinates newPosition)
{
    position = newPosition;
}

void Ball::draw(Renderer& renderer, int w, int h)
{
    int x, y;
    std::tie(x, y) = position;
    SDL_Rect rect{x - radius, y - radius, radius * 2, radius * 2};
    renderer.draw(*texture, nullptr, &rect);
//    int flipX = 0;
//    if(x < 0 + radius)
//    {
//        rect = {x - radius + w, y - radius, radius * 2, radius * 2};
//        renderer.draw(*texture, nullptr, &rect);
//        flipX = 1;
//    }
//    if(x > w - radius)
//    {
//        rect = {x - radius - w, y - radius, radius * 2, radius * 2};
//        renderer.draw(*texture, nullptr, &rect);
//        flipX = -1;
//    }
//    if(y < 0 + radius)
//    {
//        rect = {x - radius, y - radius + h, radius * 2, radius * 2};
//        renderer.draw(*texture, nullptr, &rect);
//        if(flipX)
//        {
//            rect = {x - radius + flipX * w, y - radius + h, radius * 2, radius * 2};
//            renderer.draw(*texture, nullptr, &rect);
//        }
//    }
//    if(y > h - radius)
//    {
//        rect = {x - radius, y - radius -h, radius * 2, radius * 2};
//        renderer.draw(*texture, nullptr, &rect);
//        if(flipX)
//        {
//            rect = {x - radius + flipX * w, y - radius + h, radius * 2, radius * 2};
//            renderer.draw(*texture, nullptr, &rect);
//        }
//    }

}

void Ball::step()
{
    float x, y, vX, vY, aX, aY;
    std::tie(x, y) = position;
    std::tie(vX, vY) = velociy;
    std::tie(aX, aY) = acceleration;
    vX += aX;
    vY += aY;

    position = std::make_tuple(x + vX, y + vY);
    velociy = std::make_tuple(vX, vY);
    acceleration = std::make_tuple(0.0, 0.0);
}

const Velocity& Ball::getVelocity()
{
    return velociy;
}
void Ball::setVelocity(float vX, float vY)
{
    velociy = std::make_tuple(vX, vY);
}

void Ball::setVelocity(Velocity newVelocity)
{
    velociy = newVelocity;
}

Velocity operator+(const Velocity& lhs, const Velocity& rhs)
{
    float lhsX, lhsY, rhsX, rhsY;
    std::tie(lhsX, lhsY) = lhs;
    std::tie(rhsX, rhsY) = rhs;
    return std::make_tuple(lhsX + rhsX, lhsY + rhsY);
}

Velocity operator-(const Velocity& lhs, const Velocity& rhs)
{
    float lhsX, lhsY, rhsX, rhsY;
    std::tie(lhsX, lhsY) = lhs;
    std::tie(rhsX, rhsY) = rhs;
    return std::make_tuple(lhsX - rhsX, lhsY - rhsY);
}

Velocity operator*(const Velocity& lhs, const float& rhs)
{
    float lhsX, lhsY;
    std::tie(lhsX, lhsY) = lhs;
    return std::make_tuple(lhsX * rhs, lhsY * rhs);
}
Velocity operator*(const float& lhs, const Velocity& rhs)
{
    return rhs * lhs;
}
Velocity operator/(const Velocity& lhs, const float& rhs)
{
    float lhsX, lhsY;
    std::tie(lhsX, lhsY) = lhs;
    return std::make_tuple(lhsX / rhs, lhsY / rhs);
}
