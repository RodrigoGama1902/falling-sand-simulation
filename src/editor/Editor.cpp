#include "SDL2/SDL.h"

#include "editor/Editor.h"

Editor::Editor(Simulation *simulation, Screen *screen)
{
    activeElement = simulation->sand_element;

    mScreen = screen;
    mPencil = new Pencil(simulation->GetGrid(), *simulation->sand_element);
    mBrush = new Brush(simulation->GetGrid(), *simulation->sand_element);
    mToolHandler = new ToolHandler(*mBrush);
}

Editor::~Editor()
{
}

void Editor::Render()
{
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    GetToolHandler()->GetTool()->DrawCursor(*mScreen, xMouse / mScreen->GetScreenMag(), yMouse / mScreen->GetScreenMag());
}

void Editor::Update()
{
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    GetToolHandler()->GetTool()->Draw(xMouse / mScreen->GetScreenMag(), yMouse / mScreen->GetScreenMag(), GetActiveElement());
}
