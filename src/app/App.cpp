
#include "App.h"
#include "SDL2/SDL.h"
#include "Line2D.h"
#include "grid.h"
#include "brush.h"
#include "sand.h"
#include "water.h"
#include "wall.h"
#include <iostream>
#include <time.h>
#include "AppUtils.h"

// DEBUG
const int DEBUG_SCREEN_WIDTH = 648 * 0.1;
const int DEBUG_SCREEN_HEIGHT = 364 * 0.1;
const int DEBUG_SCREEN_MAG = 20;

// PRODUCTION
const int SCREEN_WIDTH = 648 * 0.8;
const int SCREEN_HEIGHT = 364 * 0.8;
const int SCREEN_MAG = 2;

App &App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(bool debug)
{
    if (debug)
    {
        mnoptrWindow = mScreen.Init(DEBUG_SCREEN_WIDTH, DEBUG_SCREEN_HEIGHT, DEBUG_SCREEN_MAG);
        screenMag = DEBUG_SCREEN_MAG;
    }
    else
    {
        mnoptrWindow = mScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAG);
        screenMag = SCREEN_MAG;
    }

    this->debug = debug;
    return mnoptrWindow != nullptr;
}

void App::Run()
{
    if (!mnoptrWindow)
    {
        std::cout << "Error: App::Run() called before App::Init()" << std::endl;
        return;
    }

    // uint32_t SDL_GetMouseState(int *x, int *y);
    // Line2D line1(Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT), Vec2D(0, 0));
    // theScreen.Draw(line1, Color::Red());
    // theScreen.SwapScreen();

    srand(time(NULL)); // Seed the random number generator

    // Init Elements

    Sand *sand_element = new Sand();
    Water *water_element = new Water();
    Wall *wall_element = new Wall();

    // Grid grid(mScreen, sand_element, 20, debug = debug); // Create a grid with 50% cells filled - 12 FPS with 80% sand_element fill
    Grid grid(mScreen, debug = debug);

    Brush brush(&grid);

    uint32_t lastTick = SDL_GetTicks();
    uint32_t currentTick = lastTick;

    uint32_t dt = 10;
    uint32_t accumulator = 0;

    SDL_Event sdlEvent;

    bool running = true;

    while (running)
    {

        currentTick = SDL_GetTicks();
        uint32_t frameTime = currentTick - lastTick;

        if (frameTime > 300)
        {
            frameTime = 300;
        }

        lastTick = currentTick;

        if (!debug)
        {
            accumulator += frameTime;
        }

        while (SDL_PollEvent(&sdlEvent))
        {

            switch (sdlEvent.type)
            {

            case SDL_KEYUP:
                if (debug)
                {
                    accumulator += 10;
                    break;
                }

            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.y > 0)
                {
                    brush.SetBrushSize(brush.GetBrushSize() + 1);
                }
                else if (sdlEvent.wheel.y < 0)
                {
                    brush.SetBrushSize(brush.GetBrushSize() - 1);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                brush.ToggleDraw(false);
                break;

            case SDL_MOUSEBUTTONDOWN:
                brush.ToggleDraw(true);

                switch (sdlEvent.button.button)
                {
                case SDL_BUTTON_LEFT:
                    brush.SetElement(*sand_element);
                    break;
                case SDL_BUTTON_RIGHT:
                    brush.SetElement(*water_element);
                    break;
                case SDL_BUTTON_MIDDLE:
                    brush.SetElement(*wall_element);
                    break;
                default:
                    brush.SetElement(*sand_element);
                    break;
                }
                break;

            case SDL_QUIT:
                running = false;
                break;
            }
        }

        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);

        while (accumulator >= dt)
        {
            // Update current scene by dt
            grid.Update();
            DisplayFPS(frameTime);

            accumulator -= dt;

            // Brush Draw
            if (brush.is_drawing())
                brush.Draw(xMouse / screenMag, yMouse / screenMag);
        }

        // Render
        brush.DrawCursor(mScreen, xMouse / screenMag, yMouse / screenMag);

        if (debug)
        {
            grid.DrawNextData();
            mScreen.Draw(grid.GetDebugCurrentX(), grid.GetDebugCurrentY(), Color::Red());
        }
        else
        {
            grid.Draw();
        }

        mScreen.SwapScreen();
    }
}