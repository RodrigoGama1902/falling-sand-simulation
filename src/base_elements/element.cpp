#include "element.h"
#include "grid.h"
#include <iostream>

Element::Element()
{
    x_direction = rand() % 2 == 0 ? -1 : 1; // Randomize direction
    moving = false;
}

Element::~Element()
{
}
