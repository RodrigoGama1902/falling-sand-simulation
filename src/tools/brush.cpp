#include "brush.h"
#include "element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "grid.h"
#include "sand.h"

#include "Circle.h"
#include "Screen.h"

Brush::Brush(Grid *grid)
{
    mElement = nullptr;
    mGrid = grid;
    last_x_pos = -1;
    last_y_pos = -1;
}

void Brush::Draw(uint32_t x, uint32_t y)
{
    if (!drawing)
    {
        return;
    }

    mGrid->SetElement(x, y, mElement->clone());

    // mGrid->SetElement(x, y, *mElement); // this will not create a new instance of the element, but will instead just copy the pointer to the element,
    //   optimized for performance, but colors cannot be instantiated.

    last_x_pos = x;
    last_y_pos = y;
}

void Brush::DrawCursor(Screen &screen, uint32_t x, uint32_t y)
{
    Circle circle(Vec2D(x, y), brush_size);
    Color whiteColor = Color::White();
    screen.Draw(circle, whiteColor);
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

void Brush::SetElement(Element &elm)
{
    mElement = &elm;
}