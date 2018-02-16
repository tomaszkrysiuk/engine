#include "ImgInit.h"
#include <SDL_image.h>

ImgInit::ImgInit(int flags)
{
    IMG_Init(flags);
}


ImgInit::~ImgInit()
{
    IMG_Quit();
}
