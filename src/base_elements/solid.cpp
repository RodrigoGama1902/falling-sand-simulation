#include "Solid.h"
#include "Element.h"
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
