#pragma once
#include <SDL_image.h>
#include "Window.h"

class Texture;


class Renderer
{
public:
    Renderer(SDL_Renderer* renderer);
    ~Renderer();
    SDL_Renderer* get();
    void draw(const Texture&, SDL_Rect* src, SDL_Rect* dest);
    void present();
    void clear();
    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void drawLine(int x1, int y1, int x2, int y2);


//private:
    SDL_Renderer* renderer;

};
