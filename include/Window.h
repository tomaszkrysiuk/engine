#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <tuple>


class Window
{
    public:
        Window(const char* title, int x, int y, int w, int h, uint32_t flags);
        ~Window();
        void fill(uint8_t R, uint8_t G, uint8_t B);
        void fill(std::tuple<uint8_t, uint8_t, uint8_t>);
        void update();
        SDL_Window* getWindow();
        void blit(SDL_Surface*);
        SDL_Surface* getSurface();

    private:
        SDL_Window* window;
        SDL_Surface* screenSurface;
};

#endif // WINDOW_H
