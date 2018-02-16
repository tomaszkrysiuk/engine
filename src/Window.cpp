#include "Window.h"
#include <SDL.h>
#include <stdexcept>

Window::Window(const char* title, int x, int y, int w, int h, uint32_t flags)
{
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if(window == NULL)
    {
        throw std::runtime_error(SDL_GetError());
    }
    screenSurface = SDL_GetWindowSurface(window);
}

Window::~Window()
{
    if(window)
        SDL_DestroyWindow(window);
}

void Window::fill(uint8_t R, uint8_t G, uint8_t B)
{
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, R, G, B));
}

void Window::fill(std::tuple<uint8_t, uint8_t, uint8_t> color)
{
    uint8_t R, G, B;
    std::tie(R, G, B) = color;
    this->fill(R, G, B);
}

void Window::update()
{
    SDL_UpdateWindowSurface(window);
}

SDL_Window* Window::getWindow()
{
    return window;
}

void Window::blit(SDL_Surface* s)
{
   SDL_BlitSurface(s,
                   NULL,
                   screenSurface,
                   NULL);
}

SDL_Surface* Window::getSurface()
{
    return screenSurface;
}






