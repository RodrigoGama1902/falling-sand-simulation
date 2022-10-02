#include "Wall.h"
#include "StaticSolid.h"
#include "Color.h"

Wall::Wall() : StaticSolid()
{
    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 255 * m, 255);

    velocity_y = 0;
    friction = 20;
}

Wall::~Wall()
{
}
