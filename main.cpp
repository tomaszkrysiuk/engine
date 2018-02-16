#include <iostream>
#include "SdlInit.h"
#include "ImgInit.h"
#include "Window.h"
#include "Bounce.h"
#include "Renderer.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;



int main( int argc, char* args[] )
{
	SdlInit sdl(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	ImgInit sdlImg(IMG_INIT_PNG);
    uint32_t rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;

	Window window("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_MaximizeWindow(window.getWindow());
	SDL_GetWindowSize(window.getWindow(), &SCREEN_WIDTH, &SCREEN_HEIGHT);

	Renderer renderer(SDL_CreateRenderer(window.getWindow(), -1, rendererFlags));


	Bounce::startBounceLoop(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	return 0;
}

