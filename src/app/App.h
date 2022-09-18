#ifndef _APP_H_
#define _APP_H_

#include "Screen.h"
#include <stdint.h>

struct SDL_Window;

class App
{
public:
    static App &Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();

    inline uint32_t Width() const { return mScreen.Width(); }
    inline uint32_t Height() const { return mScreen.Height(); }

private:
    Screen mScreen;
    SDL_Window *mnoptrWindow;
};

#endif