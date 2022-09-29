#include "liquid.h"
#include "element.h"

#include <iostream>
#include <typeinfo>

Liquid::Liquid() : Element()
{
    spawn_probability = 10;
}

Liquid::~Liquid()
{
}

void Liquid::Update(Grid &grid, int x, int y)
{

    if (moving)
    {
        int rand_add_color = rand() % 2;

        if (rand_add_color == 1)
        {
            int new_green = elmColor.GetGreen() + 20;

            if (new_green > elmMaxColor.GetGreen())
                new_green = elmMaxColor.GetGreen();
            if (new_green < elmMinColor.GetGreen())
                new_green = elmMinColor.GetGreen();

            elmColor.SetGreen(new_green);
        }
        else
        {
            int new_green = elmColor.GetGreen() - 20;

            if (new_green > elmMaxColor.GetGreen())
                new_green = elmMaxColor.GetGreen();
            if (new_green < elmMinColor.GetGreen())
                new_green = elmMinColor.GetGreen();

            elmColor.SetGreen(new_green);
        }
    }
    else
    {
        if (elmColor.GetGreen() != elmMinColor.GetGreen())
        {
            if (currentColorFadeFrequency <= 0)
            {
                if (elmColor.GetGreen() > elmMinColor.GetGreen())
                    elmColor.SetGreen(elmColor.GetGreen() - 1);
                else if (elmColor.GetGreen() < elmMinColor.GetGreen())
                    elmColor.SetGreen(elmColor.GetGreen() + 1);
                currentColorFadeFrequency = elmColorFadeFrequency;
            }

            currentColorFadeFrequency--;
        }
    }

    moving = true;

    if (grid.GetElement(x, y + 1) == nullptr) // Check if is falling
    {
        grid.SetElement(x, y + 1, this);
        grid.SetElement(x, y, nullptr);
        velocity_y++;
    }

    else if (grid.GetElement(x + x_direction, y) == nullptr)
    {
        int new_x{x + x_direction};

        for (int i = 2; i < dispersion; i++)
        {
            if (grid.GetElement(x + (x_direction * i), y) == nullptr)
            {
                new_x = x + (x_direction * i);
            }
            else
            {
                break;
            }
        }

        grid.SetElement(new_x, y, this);
        grid.SetElement(x, y, nullptr);
    }
    else
    {
        moving = false;
        velocity_y = 0;
    }

    x_direction = rand() % 2 == 0 ? -1 : 1; // Randomize direction

    /*
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
    }*/
}