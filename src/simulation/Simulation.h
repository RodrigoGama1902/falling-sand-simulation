#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "Grid.h"

#include "Sand.h"
#include "Water.h"
#include "Honey.h"
#include "Wall.h"

class Screen;

class Simulation
{
public:
    Simulation(Screen &screen, bool debug_mode);
    ~Simulation();

    void Render();
    void Update();

    Grid *GetGrid() { return mGrid; }

    Sand *sand_element;
    Water *water_element;
    Wall *wall_element;
    Honey *honey_element;

private:
    Grid *mGrid;
    bool debugMode;
};

#endif