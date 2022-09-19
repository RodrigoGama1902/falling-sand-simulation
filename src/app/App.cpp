
#include "App.h"
#include "SDL2/SDL.h"
#include "Line2D.h"
#include "grid.h"
#include "brush.h"
#include "sand.h"
#include "water.h"
#include <iostream>

const int SCR_MAG = 3; // Screen magnification

int LAST_X = -1;
int LAST_Y = -1;

void draw_on_mouse_click(Screen &theScreen)
{
    int x, y;

    uint32_t buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0)
    {
        if (LAST_X != -1 && LAST_Y != -1)
        {
            Line2D line(LAST_X, LAST_Y, x / SCR_MAG, y / SCR_MAG);
            theScreen.Draw(line, Color::Red());
        }
        else
        {
            theScreen.Draw(x / SCR_MAG, y / SCR_MAG, Color::Red());
        }

        LAST_X = x / SCR_MAG;
        LAST_Y = y / SCR_MAG;
    }

    theScreen.SwapScreen(true);
}

App &App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    mnoptrWindow = mScreen.Init(width, height, mag);
    return mnoptrWindow != nullptr;
}

void App::Run()
{
    if (mnoptrWindow)
    {

        // uint32_t SDL_GetMouseState(int *x, int *y);
        // Line2D line1(Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT), Vec2D(0, 0));
        // theScreen.Draw(line1, Color::Red());
        // theScreen.SwapScreen();

        Grid grid(mScreen);
        Brush brush(&grid);

        // Init Elements

        Sand *sand_element = new Sand();
        Water *water_element = new Water();

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
            accumulator += frameTime;

            while (SDL_PollEvent(&sdlEvent))
            {

                switch (sdlEvent.type)
                {

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
                    default:
                        brush.SetElement(*sand_element);
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:

                    brush.Draw(sdlEvent.motion.x / SCR_MAG, sdlEvent.motion.y / SCR_MAG);
                    break;

                case SDL_QUIT:
                    running = false;
                    break;
                }
            }

            while (accumulator >= dt)
            {
                // Update current scene by dt
                grid.Update();
                accumulator -= dt;
            }

            // Render
            grid.Draw();
            mScreen.SwapScreen();
        }
    }
}