#include "water.h"
#include "element.h"

#include <iostream>
#include <typeinfo>

Water::Water() : Element()
{
    elmColor = Color(0, 124, 200, 255);
    elmMinColor = Color(0, 78, 200, 255);
    elmMaxColor = Color(0, 140, 200, 255);
    elmColorFadeFrequency = 5;
    currentColorFadeFrequency = 0;
    solid = true;
}

void Water::Update(Grid &grid, int x, int y)
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

    if (grid.GetElement(x, y + 1) == nullptr)
    {
        grid.SetElement(x, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }

    else if (grid.GetElement(x + 1, y + 1) == nullptr)
    {
        grid.SetElement(x + 1, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }

    else if (grid.GetElement(x - 1, y + 1) == nullptr)
    {
        grid.SetElement(x - 1, y + 1, this);
        grid.SetElement(x, y, nullptr);
    }

    else if (grid.GetElement(x + 1, y) == nullptr)
    {
        grid.SetElement(x + 1, y, this);
        grid.SetElement(x, y, nullptr);
    }
    else if (grid.GetElement(x - 1, y) == nullptr)
    {
        grid.SetElement(x - 1, y, this);
        grid.SetElement(x, y, nullptr);
    }
    else
    {
        moving = false;
    }

    // Checking water empty spaces
}