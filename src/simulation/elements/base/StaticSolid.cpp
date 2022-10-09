#include "simulation/elements/base/StaticSolid.h"
#include "simulation/elements/base/Solid.h"

#include <random>

StaticSolid::StaticSolid() : Solid()
{
    spawn_probability = 100;
}

StaticSolid::~StaticSolid()
{
}

void StaticSolid::UpdateColor()
{
}

void StaticSolid::Move(Grid &grid, int x, int y)
{
}

void StaticSolid::Update(Grid &grid, int x, int y)
{
}