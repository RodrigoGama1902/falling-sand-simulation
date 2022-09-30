#include "Pencil.h"

Pencil::Pencil(Grid *grid, Element &defaultElement) : PaintTool(grid, defaultElement)
{
}

Pencil::~Pencil()
{
}

void Pencil::Draw(uint32_t x, uint32_t y)
{
    mGrid->SetElement(x, y, mElement->clone());

    last_x_pos = x;
    last_y_pos = y;
}

void Pencil::DrawCursor(Screen &screen, uint32_t x, uint32_t y)
{
    screen.Draw(x, y, cursorColor);
}