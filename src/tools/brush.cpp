#include "brush.h"
#include "element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "grid.h"
#include "sand.h"

Brush::Brush(Grid *grid)
{
    mGrid = grid;
    currentElement = new Sand();
    last_x_pos = -1;
    last_y_pos = -1;
}

void Brush::Draw(uint32_t x, uint32_t y, Element &elm)
{
    if (!drawing)
    {
        return;
    }

    mGrid->SetElement(x, y, *currentElement);

    last_x_pos = x;
    last_y_pos = y;
}

void Brush::ToggleDraw(bool toggle)
{
    if (toggle)
    {
        drawing = true;
    }
    else
    {
        last_x_pos = -1;
        last_y_pos = -1;
        drawing = false;
    }
}