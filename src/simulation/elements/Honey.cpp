#include "simulation/elements/Honey.h"
#include "graphics/Color.h"

Honey::Honey() : Liquid()
{
    elmColor = Color(246, 224, 0, 255);
    elmMinColor = Color(137, 104, 0, 255);
    elmMaxColor = Color(249, 201, 1, 255);
    dispersion = 1;
    liquid_density = 200;
}

Honey::~Honey()
{
}
