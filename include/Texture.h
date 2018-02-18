#pragma once
#include <SDL_image.h>

class Renderer;

class Texture
{
public:
    Texture(Renderer& renderer, const char * file);
    Texture(SDL_Texture* texture);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    SDL_Texture* get() const;
    void setColorMod(Uint8 r, Uint8 g, Uint8 b);

private:
    SDL_Texture* texture;
};

