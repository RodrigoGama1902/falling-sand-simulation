#ifndef _APP_H_
#define _APP_H_

#include "simulation/Simulation.h"
#include "editor/Editor.h"

#include "graphics/Screen.h"
#include <stdint.h>

struct SDL_Window;
union SDL_Event;

class App
{
public:
    static App &Singleton();
    bool Init(bool debug);

    void Run();
    void Render();
    bool SimulationInput(SDL_Event &sdlEvent, Simulation &simulation, Editor &editor);

    inline uint32_t Width() const { return mScreen.Width(); }
    inline uint32_t Height() const { return mScreen.Height(); }

    int screenMag;

private:
    Screen mScreen;
    SDL_Window *mnoptrWindow;

    bool debugMode;
};

#endif