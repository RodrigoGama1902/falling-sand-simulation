#include "simulation/elements/base/Element.h"
#include "simulation/Grid.h"

#include <iostream>

Element::Element()
{
    x_direction = rand() % 2 == 0 ? -1 : 1; // Randomize direction
    odd_even_check = false;
    moving = false;
}

Element::~Element()
{
}
