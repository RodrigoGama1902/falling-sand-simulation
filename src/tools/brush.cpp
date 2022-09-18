#include "brush.h"
#include "element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "grid.h"

Brush::Brush(Grid *grid)
{
    mGrid = grid;
    currentElement = new Element();
    last_x_pos = -1;
    last_y_pos = -1;
}

void Brush::Draw(int x, int y)
{

    uint32_t buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0)
    {

        mGrid->SetElement(x, y, *currentElement);

        last_x_pos = x;
        last_y_pos = y;
    }
}