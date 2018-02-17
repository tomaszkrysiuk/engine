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
    if(restart)
    {
        restart = false;
        quit = false;
        balls.clear();
        start();
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
        case SDL_KEYDOWN:
        {
            if(e.key.keysym.sym == SDLK_SPACE)
            {
                quit = true;
                restart =true;
            }
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
    int radius = 20;
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
    static Colider c(balls, screenWidth, screenHeight);
    c.colide();
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

