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
    acceleration = std::make_tuple(aX + fX/mass, aY + fX/mass);
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

void Ball::draw(Renderer& renderer)
{
    int x, y;
    std::tie(x, y) = position;
    SDL_Rect rect{x - radius, y - radius, radius * 2, radius * 2};
    renderer.draw(*texture, nullptr, &rect);
}

void Ball::step()
{
    float x, y, vX, vY;
    std::tie(x, y) = position;
    std::tie(vX, vY) = velociy;
    position = std::make_tuple(x + vX, y + vY);
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
