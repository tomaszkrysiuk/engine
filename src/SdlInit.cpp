#include "SdlInit.h"
#include <SDL.h>
#include <stdexcept>

SdlInit::SdlInit(unsigned flags)
{
    if( SDL_Init(flags) < 0 )
    {
        throw std::runtime_error(SDL_GetError());
    }
}

SdlInit::~SdlInit()
{
    SDL_Quit();
}
