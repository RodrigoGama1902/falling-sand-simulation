#include "element.h"
#include "grid.h"
#include <iostream>

Element::Element()
{
    moving = false;
}

Element::~Element()
{
    std::cout << "Element destructor called" << std::endl;
}
