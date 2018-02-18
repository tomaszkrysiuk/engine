#pragma once
#include <tuple>
#include "Texture.h"
#include "Renderer.h"

using Coordinates = std::tuple<float, float>;
using Velocity = std::tuple<float, float>;
using Acceleration = std::tuple<float, float>;
using Force = std::tuple<float, float>;

Velocity operator+(const Velocity& lhs, const Velocity& rhs);
Velocity operator-(const Velocity& lhs, const Velocity& rhs);
Velocity operator*(const Velocity& lhs, const float& rhs);
Velocity operator*(const float& lhs, const Velocity& rhs);
Velocity operator/(const Velocity& lhs, const float& rhs);



class Ball
{
    public:
        Ball(Coordinates position, int radius, float mass, Velocity velocity, const Texture& texture);
        Ball(const Ball& ball) = default;
        Ball& operator=(const Ball& ball) = default;

        void applyForce(Force force);
        void applyForce(float fX, float fY);
        void applyAcceleration(Acceleration acceleration);


        const Velocity& getVelocity();
        void setVelocity(float vX, float vY);
        void setVelocity(Velocity);

        const Coordinates& getPosition();
        void setPosition(float x, float y);
        void setPosition(Coordinates);

        void draw(Renderer& renderer, int w, int h);
        void step();

        Coordinates position;
        int radius;
        float mass;
        Velocity velociy;
        Acceleration acceleration;
        const Texture * texture;
        bool shouldBeDestroyed = false;

};
