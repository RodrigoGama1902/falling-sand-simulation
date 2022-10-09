#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "Grid.h"
#include "ToolHandler.h"

class Screen;

class Simulation
{
public:
    Simulation(Screen &screen, bool debug_mode);
    ~Simulation();

    void Render();
    void Update();

private:
    Grid mGrid;
    bool debugMode;
};

#endif