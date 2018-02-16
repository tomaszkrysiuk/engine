#include "Texture.h"
#include "Renderer.h"
#include <stdexcept>

Texture::Texture(Renderer& renderer, const char * file)
{
    auto surface = IMG_Load(file);
    if(!surface)
        throw std::runtime_error(SDL_GetError());

    texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_FreeSurface(surface);
    if(!texture)
        throw std::runtime_error(SDL_GetError());
}

Texture::Texture(SDL_Texture* t): texture(t)
{}

SDL_Texture* Texture::get() const
{
    return texture;
}

Texture::~Texture()
{
    if(texture)
        SDL_DestroyTexture(texture);
}
