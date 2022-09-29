#include "solid.h"
#include "element.h"
#include <iostream>
#include <random>
#include <time.h>

Solid::Solid() : Element()
{
    solid = true;
    int m = rand() % 100;
    elmColor = Color(255 * m, 255 * m, 0 * m, 255);
    x_direction = rand() % 2 == 0 ? -1 : 1; // Randomize direction
    velocity_y = 0;
    friction = 20;

    spawn_probability = 10;
}

Solid::~Solid()
{
}

void Solid::Update(Grid &grid, int x, int y)
{

    if (grid.GetElement(x, y + 1) != nullptr && !grid.GetElement(x, y + 1)->solid)
    {
        grid.SwapElements(x, y, x, y + 1);
        y += 1;
    }

    if (grid.GetElement(x, y + 1) == nullptr) // Check if is falling
    {
        grid.SetElement(x, y + 1, this);
        grid.SetElement(x, y, nullptr);
        velocity_y++;
    }

    else if (grid.GetElement(x + (x_direction * -1), y + 1) == nullptr)
    {
        grid.SetElement(x + (x_direction * -1), y + 1, this);
        grid.SetElement(x, y, nullptr);
    }

    else if (grid.GetElement(x + x_direction, y + 1) == nullptr)
    {
        grid.SetElement(x + x_direction, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }

    else if (velocity_y > 0)
    {
        if (grid.GetElement(x + x_direction, y) == nullptr)
        {
            grid.SetElement(x + x_direction, y, this);
            grid.SetElement(x, y, nullptr);
            velocity_y -= friction;
        }
        else if (grid.GetElement(x + x_direction, y + 1) == nullptr)
        {
            grid.SetElement(x + x_direction, y + 1, this);
            grid.SetElement(x, y, nullptr);
            velocity_y -= friction;
        }
    }

    else
    {
        velocity_y = 0;
    }
}