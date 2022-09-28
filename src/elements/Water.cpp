#include "Water.h"
#include "Color.h"

Water::Water() : Liquid()
{
    elmColor = Color(0, 124, 200, 255);
    elmMinColor = Color(0, 78, 200, 255);
    elmMaxColor = Color(0, 140, 200, 255);
}

Water::~Water()
{
}
