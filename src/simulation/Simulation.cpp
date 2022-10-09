#include "Simulation.h"
#include "grid.h"
#include "Screen.h"

Simulation::Simulation(Screen &screen, bool debug_mode)
    : mGrid(screen), debugMode(debug_mode)
{
}

void Simulation::Render()
{
    mGrid.Draw();

    if (debugMode)
        mGrid.DrawDebuggerPointer();
}

void Simulation::Update()
{
    if (debugMode)
        mGrid.DebugUpdate(true, mGrid.GetPointerFullSkip());
    else
        mGrid.Update();
}
