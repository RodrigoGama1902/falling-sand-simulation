#include "SDL2/SDL.h"

#include "App.h"
#include "AppUtils.h"

#include "Simulation.h"
#include "Editor.h"

#include <iostream>

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

bool App::Init(bool debugMode)
{
    if (debugMode)
    {
        mnoptrWindow = mScreen.Init(DEBUG_SCREEN_WIDTH, DEBUG_SCREEN_HEIGHT, DEBUG_SCREEN_MAG);
        screenMag = DEBUG_SCREEN_MAG;
    }
    else
    {
        mnoptrWindow = mScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAG);
        screenMag = SCREEN_MAG;
    }

    this->debugMode = debugMode;
    return mnoptrWindow != nullptr;
}

void App::Run()
{
    if (!mnoptrWindow)
    {
        std::cout << "Error: App::Run() called before App::Init()" << std::endl;
        return;
    }

    Simulation simulation(mScreen, debugMode);
    Editor editor(&simulation);

    uint32_t lastTick = SDL_GetTicks();
    uint32_t currentTick = lastTick;

    uint32_t dt = debugMode ? 50 : 10;
    uint32_t accumulator = 0;

    SDL_Event sdlEvent;

    bool running = true;

    while (running)
    {
        currentTick = SDL_GetTicks();
        uint32_t frameTime = currentTick - lastTick;

        if (frameTime > 300)
            frameTime = 300;

        lastTick = currentTick;

        if (!debugMode)
            accumulator += frameTime;

        while (SDL_PollEvent(&sdlEvent)) // App Input Handling
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
                    editor.SetActiveElement(simulation.sand_element);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_2)
                {
                    editor.SetActiveElement(simulation.water_element);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_3)
                {
                    editor.SetActiveElement(simulation.wall_element);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_4)
                {
                    editor.SetActiveElement(simulation.honey_element);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_BACKSPACE)
                {
                    simulation.GetGrid()->Clear();
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_RIGHT && debugMode)
                {
                    simulation.GetGrid()->SetIsPointerSkipping(true);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_DOWN && debugMode)
                {
                    simulation.GetGrid()->SetIsPointerFullSkip(true);
                    break;
                }

                break;

            case SDL_KEYUP:
                if (sdlEvent.key.keysym.sym == SDLK_RIGHT && debugMode)
                {
                    simulation.GetGrid()->SetIsPointerSkipping(false);
                    break;
                }

                if (sdlEvent.key.keysym.sym == SDLK_DOWN && debugMode)
                {
                    simulation.GetGrid()->SetIsPointerFullSkip(false);
                    break;
                }

                break;

            case SDL_MOUSEWHEEL:

                if (sdlEvent.wheel.y > 0)
                {
                    editor.GetBrush()->SetBrushSize(editor.GetBrush()->GetBrushSize() + 1);
                    break;
                }
                else if (sdlEvent.wheel.y < 0)
                {
                    editor.GetBrush()->SetBrushSize(editor.GetBrush()->GetBrushSize() - 1);
                    break;
                }

                break;

            case SDL_MOUSEBUTTONUP:
                editor.GetToolHandler()->GetTool()->ToggleDraw(false);

                switch (sdlEvent.button.button)
                {
                case SDL_BUTTON_MIDDLE:
                    editor.GetToolHandler()->SetTool(editor.GetBrush());
                    break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:

                switch (sdlEvent.button.button)
                {
                case SDL_BUTTON_LEFT:
                    editor.GetToolHandler()->SetTool(editor.GetBrush());
                    editor.GetToolHandler()->GetTool()->ToggleDraw(true);
                    editor.GetToolHandler()->GetTool()->SetErasing(false);
                    break;
                case SDL_BUTTON_RIGHT:
                    editor.GetToolHandler()->GetTool()->ToggleDraw(true);
                    editor.GetToolHandler()->GetTool()->SetErasing(true);
                    break;
                case SDL_BUTTON_MIDDLE:
                    editor.GetToolHandler()->SetTool(editor.GetPencil());
                    editor.GetToolHandler()->GetTool()->ToggleDraw(true);
                    editor.GetToolHandler()->GetTool()->SetErasing(false);
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

        if (simulation.GetGrid()->GetPointerSkipping())
            accumulator += 1;

        if (simulation.GetGrid()->GetPointerFullSkip())
            accumulator += 50;

        while (accumulator >= dt) // Update Scene
        {
            simulation.Update();
            editor.GetToolHandler()->GetTool()->Draw(xMouse / screenMag, yMouse / screenMag, editor.GetActiveElement());
            DisplayFPS(frameTime);

            accumulator -= dt;
        }

        // Render Scene
        simulation.Render();
        editor.GetToolHandler()->GetTool()->DrawCursor(mScreen, xMouse / screenMag, yMouse / screenMag);

        mScreen.SwapScreen();
    }
}