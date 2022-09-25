#include "AppUtils.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <iomanip>
#include <ios>

static uint32_t maxFPS = 0;
static uint32_t minFPS = -1;

void DisplayFPS(uint32_t frameTime)
{
    if (SDL_GetTicks() > 3000) // Starting FPS counter after app stabilization
    {
        uint32_t fps = (frameTime > 0) ? 1000.0f / frameTime : 0.0f;

        if (fps > maxFPS)
            maxFPS = fps;
        if (fps < minFPS)
            minFPS = fps;

        std::cout << "\r" << std::setw(3) << fps << " FPS"
                  << " | " << std::setw(3) << maxFPS << " Max FPS"
                  << " | " << std::setw(3) << minFPS << " Min FPS" << std::flush;
    }
}