#include "element.h"
#include <iostream>

Element::Element() : elmColor(0, 0, 0, 0)
{
}

Element::~Element()
{
}

void Element::Update()
{
}

void Element::Render()
{
    std::cout << "Element::Render()" << std::endl;
}