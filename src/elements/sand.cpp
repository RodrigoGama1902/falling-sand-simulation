#include "sand.h"
#include "element.h"
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
    friction = 20;
}

void Sand::Update(Grid &grid, int x, int y)
{
    if (grid.GetElement(x, y + 1) == nullptr) // Check if is falling
    {
        grid.SetElement(x, y + 1, this);
        grid.SetElement(x, y, nullptr);
        velocity_y++;
        moving = true;
        return; // return since nothing can be done
    }

    // Getting random x direction check

    int x_direction;
    int x_inverse_direction;

    if (velocity_direction == -1)
        velocity_direction = rand() % 2;

    if (velocity_direction == 0)
    {
        x_direction = x + 1;
        x_inverse_direction = x - 1;
    }
    else
    {
        x_direction = x - 1;
        x_inverse_direction = x + 1;
    }

    if (velocity_y > 0)
    {
        if (grid.GetElement(x_direction, y) == nullptr)
        {
            grid.SetElement(x_direction, y, this);
            grid.SetElement(x, y, nullptr);
            velocity_y -= friction;
            return;
        }
    }

    if (grid.GetElement(x_direction, y + 1) == nullptr)
    {
        grid.SetElement(x_direction, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }
    else if (grid.GetElement(x_inverse_direction, y + 1) == nullptr)
    {
        grid.SetElement(x_inverse_direction, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }
    else
    {
        velocity_direction = -1;
        velocity_y = 0;
        moving = false;
    }
}