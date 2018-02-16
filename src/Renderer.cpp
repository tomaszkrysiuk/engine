#include "Renderer.h"
#include "Texture.h"

Renderer::Renderer(SDL_Renderer* r): renderer(r)
{
}

Renderer::~Renderer()
{
    if(renderer)
        SDL_DestroyRenderer(renderer);
}

SDL_Renderer* Renderer::get()
{
    return renderer;
}

void Renderer::draw(const Texture& texture, SDL_Rect* src, SDL_Rect* dest)
{
    SDL_RenderCopy(renderer, texture.get(), src, dest);
}

void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::clear()
{
    SDL_RenderClear(renderer);
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
