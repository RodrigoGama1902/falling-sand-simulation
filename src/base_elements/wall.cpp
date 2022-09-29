#include "wall.h"
#include "element.h"
#include <iostream>

Wall::Wall() : Element()
{
    solid = true;

    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 255 * m, 255);

    spawn_probability = 100;
}

Wall::~Wall()
{
}

void Wall::Update(Grid &grid, int x, int y)
{
}