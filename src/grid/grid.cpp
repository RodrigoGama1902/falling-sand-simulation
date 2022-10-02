#include "grid.h"
#include <iostream>
#include "Screen.h"
#include "element.h"
#include "Sand.h"
#include "Wall.h"

Grid::Grid(Screen &srcScreen) : Grid(srcScreen, new Sand(), 0)
{
}

Grid::Grid(Screen &mScreen, Element *elmFill, int fillPercent)
{
    odd_even_check = true;

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

void Grid::DebugUpdate(bool fullSkip)
{
    if (fullSkip)
    {
        while (debugCurrentY < mHeight)
        {
            while (debugCurrentX < mWidth)
            {
                if (gridData[debugCurrentX][debugCurrentY] != nullptr && gridData[debugCurrentX][debugCurrentY]->odd_even_check != odd_even_check)
                {
                    gridData[debugCurrentX][debugCurrentY]->odd_even_check = odd_even_check;
                    gridData[debugCurrentX][debugCurrentY]->Update(*this, debugCurrentX, debugCurrentY);
                }
                debugCurrentX++;
            }
            debugCurrentX = 0;
            debugCurrentY++;
        }

        debugCurrentX = 0;
        debugCurrentY = 0;

        odd_even_check = !odd_even_check;
        return;
    }

    while (gridData[debugCurrentX][debugCurrentY] == nullptr)
    {
        debugCurrentX++;

        if (debugCurrentX >= mWidth)
        {
            debugCurrentX = 0;
            debugCurrentY++;
            if (debugCurrentY >= mHeight)
            {
                debugCurrentY = 0;
                odd_even_check = !odd_even_check;
                return;
            }
        }
    }

    gridData[debugCurrentX][debugCurrentY]->odd_even_check = odd_even_check;
    gridData[debugCurrentX][debugCurrentY]->Update(*this, debugCurrentX, debugCurrentY);

    debugCurrentX++;
    if (debugCurrentX >= mWidth)
    {
        debugCurrentX = 0;
        debugCurrentY++;
        if (debugCurrentY >= mHeight)
        {
            debugCurrentY = 0;
        }
    }

    odd_even_check = !odd_even_check;
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

void Grid::SetElement(uint32_t x, uint32_t y, Element *elm)
{
    if (x >= mWidth || y >= mHeight)
    {
        return;
    }

    gridData[x][y] = elm;
}

void Grid::RemoveElement(uint32_t x, uint32_t y)
{
    if (x >= mWidth || y >= mHeight)
    {
        return;
    }
    delete gridData[x][y];
    gridData[x][y] = nullptr;
}

void Grid::Clear()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            gridData[x][y] = nullptr;
        }
    }
}

Element *Grid::GetElement(uint32_t x, uint32_t y)
{
    if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
    {
        return new Wall();
    }

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
