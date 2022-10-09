#include "simulation/elements/base/Solid.h"
#include "simulation/elements/base/Element.h"
#include <iostream>
#include <random>
#include <time.h>

Solid::Solid() : Element()
{
    solid = true;
    velocity_y = 0;
}

Solid::~Solid()
{
}

void Solid::UpdateColor()
{
}
