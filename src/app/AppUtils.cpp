#include "AppUtils.h"
#include <iostream>
#include <iomanip>
#include <ios>

void DisplayFPS(uint32_t frameTime)
{
    int fps = (frameTime > 0) ? 1000.0f / frameTime : 0.0f;
    std::cout << "\r" << std::setw(3) << fps << " FPS" << std::flush;
}