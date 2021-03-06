#include "Bounce.h"
#include "Ball.h"
#include "Texture.h"
#include "SDL.h"
#include "vector"
#include <iostream>
#include <tuple>
#include <memory>
#include <algorithm>
#include "NonElasticColider.h"
#include "KeplerColider.h"
#include "SnowColider.h"
#include <stdlib.h>


Bounce::Bounce(Renderer& r, int w, int h):
    screenWidth(w),
    screenHeight(h),
    renderer(r) {}

namespace
{
const float G = 0;
}


void Bounce::start()
{
    makeSnow(1000);
    while(!quit)
    {
        handleEvents();
        applyGravity(G);
        applyColisions();
        destroyIfNeeded();
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
                balls.clear();
            }
            if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
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
            if(e.button.button == 1)
                addBlackBall();
            if(e.button.button == 2)
                addRedBall();
            if(e.button.button == 3)
                addWhiteBall();
            break;
        }
        }
    }
}


void Bounce::addBlackBall()
{
    static Texture blackBall(renderer, "./data/img/circle.png");
    int radius = 5;
    float mass = 1.0;
    balls.emplace(balls.end(),
                  Coordinates{xStart, yStart},
                  radius,
                  mass,
                  Velocity{(xStop - xStart)/15.0,
                           (yStop - yStart)/15.0},
                  blackBall);
}

void Bounce::addWhiteBall()
{
    static Texture whiteBall(renderer, "./data/img/circle2.png");
    int radius = 7;
    float mass = 10;
    balls.emplace(balls.end(),
                  Coordinates{xStart, yStart},
                  radius,
                  mass,
                  Velocity{(xStop - xStart)/15.0,
                           (yStop - yStart)/15.0},
                  whiteBall);
}

void Bounce::addRedBall()
{
    static Texture redBall(renderer, "./data/img/circle2.png");
    redBall.setColorMod(0xFF, 0x00, 0x00);
    int radius = 10;
    float mass = 200;
    balls.emplace(balls.end(),
                  Coordinates{xStart, yStart},
                  radius,
                  mass,
                  Velocity{(xStop - xStart)/15.0,
                           (yStop - yStart)/15.0},
                  redBall);
}

void Bounce::applyColisions()
{
    static std::unique_ptr<Colider> c = std::make_unique<SnowColider>(balls,
                                        screenWidth,
                                        screenHeight);
    c->colide();
}

void Bounce::applyGravity(float g)
{
    for(auto& b : balls)
        b.applyAcceleration({0.0, g});
}

void Bounce::drawAndPresent()
{
    renderer.clear();

    if(shouldDrawLine)
        drawLine();

    drawBalls();

    renderer.setDrawColor(0x200, 0x200, 0x250, 255);
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
        ball.draw(renderer, screenWidth, screenHeight);
    }
}

void Bounce::destroyIfNeeded()
{
    balls.erase(std::remove_if(balls.begin(),
                               balls.end(),
                               [](Ball& b)
    {
        return b.shouldBeDestroyed;
    }),
    balls.end());
}

void Bounce::makeSnow(int count)
{

    static Texture whiteBall(renderer, "./data/img/flake.png");
    SDL_SetTextureAlphaMod(whiteBall.get(), 230);
    for(int i = 0; i < count; i++)
    {
        float mass = 1;
        balls.emplace(balls.end(),
                      Coordinates{0, screenHeight + 100},
                      1,
                      1,
                      Velocity{5,5},
                      whiteBall);
    }
}
