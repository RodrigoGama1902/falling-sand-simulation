#include "sand.h"
#include "element.h"
#include "null.h"
#include <iostream>
#include <random>
#include <time.h>

Sand::Sand() : Element()
{
    solid = true;
    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 0 * m, 255);
    velocity_y = 0;
    velocity_direction = -1;
    friction = 10;
}

void Sand::Update(Grid &grid, int x, int y)
{

    Null *null_elm = new Null();

    // stop at screen y edge

    if (y + 1 >= grid.GetHeight())
    {
        return;
    }

    if (grid.GetElement(x, y + 1).solid == false) // Check if is falling
    {
        grid.SetElement(x, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
        velocity_y++;
        moving = true;
        return; // return since nothing can be done
    }

    if (velocity_y > 0)
    {
        if (velocity_direction == -1)
            velocity_direction = rand() % 2;

        int x_check;

        if (velocity_direction == 0)
            x_check = x + 1;
        else
            x_check = x - 1;

        if (grid.GetElement(x_check, y).solid == false)
        {
            grid.SetElement(x_check, y, *this);
            grid.SetElement(x, y, *null_elm);
            velocity_y -= friction;
            return;
        }
    }
    else
    {
        velocity_direction = -1;
        velocity_y = 0;
    }

    if (grid.GetElement(x + 1, y + 1).solid == false)
    {
        grid.SetElement(x + 1, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
        return;
    }

    if (grid.GetElement(x - 1, y + 1).solid == false)
    {
        grid.SetElement(x - 1, y + 1, *this);
        grid.SetElement(x, y, *null_elm);
        return;
    }
}