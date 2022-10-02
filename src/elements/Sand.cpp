#include "MovableSolid.h"
#include "Sand.h"
#include "Color.h"

Sand::Sand() : MovableSolid()
{
    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 0 * m, 255);

    velocity_y = 0;
    friction = 20;
}

Sand::~Sand()
{
}
