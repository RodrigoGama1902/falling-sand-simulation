#ifndef _APP_H_
#define _APP_H_

#include "Screen.h"
#include <stdint.h>

struct SDL_Window;

class App
{
public:
    static App &Singleton();
    bool Init(bool debug);
    void Run();

    inline uint32_t Width() const { return mScreen.Width(); }
    inline uint32_t Height() const { return mScreen.Height(); }

    void togglePointerSkipping(bool toggle);
    bool GetPointerSkipping() const { return isPointerSkipping; };

    int screenMag;

private:
    Screen mScreen;
    SDL_Window *mnoptrWindow;

    bool debug;
    bool isPointerSkipping;
};

#endif