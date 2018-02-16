#include "Bounce.h"
#include "Ball.h"
#include "Texture.h"
#include "SDL.h"
#include "vector"
#include <tuple>

namespace Bounce
{
void startBounceLoop(Renderer& renderer, int screenWidth, int screenHeight)
{
    Texture blackBall(renderer, "circle.png");
    std::vector<Ball> balls;
    //balls.emplace(balls.end(), Coordinates{600, 600}, 50, (float)1.0, Velocity{-4, -4}, blackBall);
    //Ball ball({600, 600}, 50, 1.0, {-1, -1}, blackBall);

    renderer.setDrawColor(150, 120, 0, 255);

    int xStart, xStop, yStart, yStop;
    bool drawLine = false;
    bool quit = false;
    while(!quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                xStart = e.button.x;
                yStart = e.button.y;
                drawLine = true;
            }
            if(e.type == SDL_MOUSEMOTION)
            {
                xStop = e.motion.x;
                yStop = e.motion.y;
            }
            if(e.type == SDL_MOUSEBUTTONUP)
            {
                xStop = e.button.x;
                yStop = e.button.y;
                drawLine = false;
                balls.emplace(balls.end(), Coordinates{xStart, yStart}, 10, (float)1.0, Velocity{(xStop - xStart)/20, (yStop - yStart)/20}, blackBall);
            }
        }









        // rysowanie i odbijanie
        renderer.clear();
        renderer.setDrawColor(150, 120, 0, 255);
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
        if(drawLine)
        {
            renderer.clear();
            renderer.setDrawColor(255, 255, 255, 255);
            renderer.drawLine(xStart, yStart, xStop, yStop);
            renderer.setDrawColor(150, 120, 0, 255);
        }

        for(auto& ball : balls)
        {
            ball.step();
            ball.draw(renderer);
        }




        renderer.present();
    }
}

}
