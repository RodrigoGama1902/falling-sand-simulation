
#include "App.h"
#include "SDL2/SDL.h"
#include "Line2D.h"
#include "Grid.h"

#include <iostream>
#include <time.h>
#include "AppUtils.h"

#include "ToolHandler.h"
#include "Pencil.h"
#include "Brush.h"

#include "Sand.h"
#include "Water.h"
#include "Honey.h"
#include "Wall.h"

// DEBUG
const int DEBUG_SCREEN_WIDTH = 648 * 0.1;
const int DEBUG_SCREEN_HEIGHT = 364 * 0.1;
const int DEBUG_SCREEN_MAG = 20;

// PRODUCTION
const int SCREEN_WIDTH = 648 * 0.8;
const int SCREEN_HEIGHT = 364 * 0.8;
const int SCREEN_MAG = 3;

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
    Honey *honey_element = new Honey();

    Element *active_element = sand_element;

    // Grid grid(mScreen, sand_element, 20, debug = debug); // Create a grid with 50% cells filled - 12 FPS with 80% sand_element fill
    Grid grid(mScreen);

    Brush brush(&grid, *sand_element);
    Pencil pencil(&grid, *sand_element);

    ToolHandler toolHandler(brush);

    uint32_t lastTick = SDL_GetTicks();
    uint32_t currentTick = lastTick;

    uint32_t dt = debug ? 50 : 10;
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

            case SDL_KEYDOWN:

                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_1)
                {
                    active_element = sand_element;
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_2)
                {
                    active_element = water_element;
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_3)
                {
                    active_element = wall_element;
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_4)
                {
                    active_element = honey_element;
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_BACKSPACE)
                {
                    grid.Clear();
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_RIGHT && debug)
                {
                    grid.SetIsPointerSkipping(true);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_DOWN && debug)
                {
                    grid.SetIsPointerFullSkip(true);
                    break;
                }

                break;

            case SDL_KEYUP:
                if (sdlEvent.key.keysym.sym == SDLK_RIGHT && debug)
                {
                    grid.SetIsPointerSkipping(false);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_DOWN && debug)
                {
                    grid.SetIsPointerFullSkip(false);
                    break;
                }

                break;

            case SDL_MOUSEWHEEL:

                if (sdlEvent.wheel.y > 0)
                {
                    brush.SetBrushSize(brush.GetBrushSize() + 1);
                    break;
                }
                else if (sdlEvent.wheel.y < 0)
                {
                    brush.SetBrushSize(brush.GetBrushSize() - 1);
                    break;
                }

                break;

            case SDL_MOUSEBUTTONUP:
                toolHandler.GetTool()->ToggleDraw(false);

                switch (sdlEvent.button.button)
                {
                case SDL_BUTTON_MIDDLE:
                    toolHandler.SetTool(&brush);
                    break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:

                switch (sdlEvent.button.button)
                {
                case SDL_BUTTON_LEFT:
                    toolHandler.SetTool(&brush);
                    toolHandler.GetTool()->ToggleDraw(true);
                    toolHandler.GetTool()->SetErasing(false);
                    break;
                case SDL_BUTTON_RIGHT:
                    toolHandler.GetTool()->ToggleDraw(true);
                    toolHandler.GetTool()->SetErasing(true);
                    break;
                case SDL_BUTTON_MIDDLE:
                    toolHandler.SetTool(&pencil);
                    toolHandler.GetTool()->ToggleDraw(true);
                    toolHandler.GetTool()->SetErasing(false);
                    break;
                default:
                    break;
                }
                break;

            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }

        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);

        if (grid.GetPointerSkipping())
            accumulator += 1;

        if (grid.GetPointerFullSkip())
            accumulator += 50;

        while (accumulator >= dt)
        {
            // Update current scene by dt
            if (toolHandler.GetTool()->is_drawing())
                toolHandler.GetTool()->Draw(xMouse / screenMag, yMouse / screenMag, active_element);

            if (debug)
                grid.DebugUpdate(true, grid.GetPointerFullSkip());
            else
                grid.Update();

            DisplayFPS(frameTime);
            accumulator -= dt;
        }

        // Render

        grid.Draw();

        if (debug)
            grid.DrawDebuggerPointer();

        toolHandler.GetTool()->DrawCursor(mScreen, xMouse / screenMag, yMouse / screenMag);

        mScreen.SwapScreen();
    }
}