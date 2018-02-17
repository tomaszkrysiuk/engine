#include "Bounce.h"
#include "Ball.h"
#include "Texture.h"
#include "SDL.h"
#include "vector"
#include <tuple>


Bounce::Bounce(Renderer& r, int w, int h):
    screenWidth(w),
    screenHeight(h),
    renderer(r) {}




void Bounce::start()
{
    while(!quit)
    {
        handleEvents();
        applyColisions();
        drawAndPresent();
    }
}

void Bounce::handleEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
        case SDL_QUIT:
        {
            quit = true;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            xStart = e.button.x;
            yStart = e.button.y;
            shouldDrawLine = true;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            xStop = e.motion.x;
            yStop = e.motion.y;
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            xStop = e.button.x;
            yStop = e.button.y;
            shouldDrawLine = false;
            addBlackBall();
            break;
        }
        }
    }
}


void Bounce::addBlackBall()
{
    static Texture blackBall(renderer, "circle.png");
    int radius = 10;
    float mass = 1.0;
    balls.emplace(balls.end(),
                  Coordinates{xStart, yStart},
                  radius,
                  mass,
                  Velocity{(xStop - xStart)/20.0,
                           (yStop - yStart)/20.0},
                  blackBall);
}

void Bounce::applyColisions()
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

void Bounce::drawAndPresent()
{
    renderer.clear();

    if(shouldDrawLine)
        drawLine();

    drawBalls();

    renderer.setDrawColor(150, 120, 0, 255);
    renderer.present();
}

void Bounce::drawLine()
{
    renderer.setDrawColor(255, 255, 255, 255);
    renderer.drawLine(xStart, yStart, xStop, yStop);
}

void Bounce::drawBalls()
{
    for(auto& ball : balls)
    {
        ball.step();
        ball.draw(renderer);
    }
}

