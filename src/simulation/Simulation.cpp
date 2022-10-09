#include "Simulation.h"
#include "grid.h"
#include "Screen.h"

#include <time.h>

Simulation::Simulation(Screen &screen, bool debug_mode)
    : mGrid(screen), debugMode(debug_mode)
{
    srand(time(NULL)); // Seed the random number generator

    sand_element = new Sand();
    water_element = new Water();
    wall_element = new Wall();
    honey_element = new Honey();
}

Simulation::~Simulation()
{
    delete sand_element;
    delete water_element;
    delete wall_element;
    delete honey_element;
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
