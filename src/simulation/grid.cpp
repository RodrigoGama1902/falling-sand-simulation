#include "Grid.h"
#include <iostream>
#include "graphics/Screen.h"
#include "simulation/elements/base/Element.h"
#include "simulation/elements/Sand.h"
#include "simulation/elements/Wall.h"

Grid::Grid(Screen &srcScreen) : Grid(srcScreen, new Sand(), 0)
{
}

Grid::Grid(Screen &mScreen, Element *elmFill, int fillPercent)
{
    odd_even_check = true;
    show_debugger_pointer = false;

    mWidth = mScreen.Width();
    mHeight = mScreen.Height();

    this->mScreen = &mScreen;

    debugCurrentX = 0;
    debugCurrentY = 0;

    gridData = std::vector<std::vector<Element *>>(mWidth, std::vector<Element *>(mHeight));

    for (uint32_t x = 0; x < mWidth; x++)
    {
        for (uint32_t y = 0; y < mHeight; y++)
        {
            if (rand() % 100 < fillPercent)
                gridData[x][y] = elmFill->clone();
        }
    }
}

Grid::~Grid()
{
    for (uint32_t x = 0; x < mWidth; x++)
    {
        for (uint32_t y = 0; y < mHeight; y++)
        {
            if (gridData[x][y] != nullptr)
                delete gridData[x][y];
        }
    }
}

void Grid::DebugUpdate(bool skip_update_null_elements, bool full_grid_update)
{
    // full_grid_update is a recursion that will update all the rest of the grid positions that was not updated

    if (full_grid_update)
    {
        show_debugger_pointer = false;
        bool current_odd_even_check = odd_even_check;

        while (current_odd_even_check == odd_even_check)
            DebugUpdate(false, false);

        isPointerFullSkip = false;
        return;
    }
    // else
    //{
    //     show_debugger_pointer = true;
    // }

    // skip_update_null_elements is a recursion that will keeping updating the current grid position
    // until it finds a element that is not null, so these grid positions that have null elements will be updated
    // but not shown on the debug screen

    if (skip_update_null_elements)
    {
        int max_iterations = mWidth * mHeight;
        int current_iteration = 0;

        while (gridData[debugCurrentX][debugCurrentY] == nullptr && current_iteration < max_iterations)
        {
            DebugUpdate(false, false);
            current_iteration++;
        }
    }

    // This is the core of the debug update, it will update the current grid position, and then move to the next one

    if (gridData[debugCurrentX][debugCurrentY] != nullptr && gridData[debugCurrentX][debugCurrentY]->odd_even_check != odd_even_check)
    {
        gridData[debugCurrentX][debugCurrentY]->odd_even_check = odd_even_check;
        gridData[debugCurrentX][debugCurrentY]->Update(*this, debugCurrentX, debugCurrentY);
    }

    if (odd_even_check)
        debugCurrentX++;
    else
        debugCurrentX--;

    if (debugCurrentX >= mWidth)
    {
        debugCurrentX = odd_even_check ? 0 : mWidth - 1;
        debugCurrentY++;

        if (debugCurrentY >= mHeight)
        {
            debugCurrentY = 0;
            odd_even_check = !odd_even_check;
        }
    }
}

void Grid::Update()
{
    if (odd_even_check)
    {
        for (uint32_t y = 0; y < mHeight; y++)
        {
            for (uint32_t x = 0; x < mWidth; x++)
            {
                if (gridData[x][y] != nullptr && gridData[x][y]->odd_even_check != odd_even_check)
                {
                    gridData[x][y]->odd_even_check = odd_even_check;
                    gridData[x][y]->Update(*this, x, y);
                }
            }
        }
    }
    else
    {
        for (uint32_t y = 0; y < mHeight; y++)
        {
            for (int32_t x = mWidth - 1; x >= 0; x--)
            {
                if (gridData[x][y] != nullptr && gridData[x][y]->odd_even_check != odd_even_check)
                {
                    gridData[x][y]->odd_even_check = odd_even_check;
                    gridData[x][y]->Update(*this, x, y);
                }
            }
        }
    }

    odd_even_check = !odd_even_check;
}

void Grid::Draw()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            if (gridData[x][y] != nullptr)
            {
                mScreen->Draw(x, y, *gridData[x][y]);
            }
        }
    }
}

void Grid::DrawDebuggerPointer()
{
    if (show_debugger_pointer)
        mScreen->Draw(GetDebugCurrentX(), GetDebugCurrentY(), Color::Red());
};

void Grid::SetElement(uint32_t x, uint32_t y, Element *elm)
{
    if (x >= mWidth || y >= mHeight)
        return;

    gridData[x][y] = elm;
}

void Grid::RemoveElement(uint32_t x, uint32_t y)
{
    if (x >= mWidth || y >= mHeight)
        return;

    if (gridData[x][y] != nullptr)
    {
        delete gridData[x][y];
        gridData[x][y] = nullptr;
    }
}

void Grid::Clear()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
            RemoveElement(x, y);
    }
}

Element *Grid::GetElement(uint32_t x, uint32_t y)
{
    if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
        return new Wall();

    return gridData[x][y];
}

void Grid::SwapElements(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    Element *temp = gridData[x1][y1];

    gridData[x1][y1] = gridData[x2][y2];
    gridData[x2][y2] = temp;

    gridData[x1][y1]->odd_even_check = odd_even_check;
    gridData[x2][y2]->odd_even_check = odd_even_check;
}
