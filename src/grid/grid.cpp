#include "grid.h"
#include <iostream>
#include "Screen.h"
#include "element.h"
#include "solid.h"
#include "wall.h"

Grid::Grid(Screen &srcScreen) : Grid(srcScreen, new Solid(), 0)
{
}

Grid::Grid(Screen &mScreen, Element *elmFill, int fillPercent)
{
    mWidth = mScreen.Width();
    mHeight = mScreen.Height();
    this->mScreen = &mScreen;

    debugCurrentX = 0;
    debugCurrentY = 0;

    gridData = std::vector<std::vector<Element *>>(mWidth, std::vector<Element *>(mHeight));
    gridDataNext = std::vector<std::vector<Element *>>(mWidth, std::vector<Element *>(mHeight));

    for (uint32_t x = 0; x < mWidth; x++)
    {
        for (uint32_t y = 0; y < mHeight; y++)
        {
            if (rand() % 100 < fillPercent)
                gridDataNext[x][y] = elmFill->clone();
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
            if (gridDataNext[x][y] != nullptr)
                delete gridDataNext[x][y];
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
                if (gridData[debugCurrentX][debugCurrentY] != nullptr)
                    gridData[debugCurrentX][debugCurrentY]->Update(*this, debugCurrentX, debugCurrentY);
                debugCurrentX++;
            }
            debugCurrentX = 0;
            debugCurrentY++;
        }
        SwapGrids();

        debugCurrentX = 0;
        debugCurrentY = 0;

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
                SwapGrids();
                return;
            }
        }
    }

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
}

void Grid::Update()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            if (gridData[x][y] != nullptr)
            {
                gridData[x][y]->Update(*this, x, y);
            }
        }
    }

    SwapGrids();
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

void Grid::DrawNextData()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            if (gridDataNext[x][y] != nullptr)
            {
                mScreen->Draw(x, y, *gridDataNext[x][y]);
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

    gridDataNext[x][y] = elm;
}

void Grid::RemoveElement(uint32_t x, uint32_t y)
{
    if (x >= mWidth || y >= mHeight)
    {
        return;
    }

    gridDataNext[x][y] = nullptr;
    gridData[x][y] = nullptr;
}

void Grid::Clear()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            gridDataNext[x][y] = nullptr;
        }
    }

    SwapGrids();
}

Element *Grid::GetElement(uint32_t x, uint32_t y)
{
    if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
    {
        return new Wall();
    }

    return gridDataNext[x][y];
}

void Grid::SwapElements(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    Element *temp = gridData[x1][y1];
    gridDataNext[x1][y1] = gridDataNext[x2][y2];
    gridDataNext[x2][y2] = temp;
}

void Grid::SwapGrids()
{
    gridData = gridDataNext;
}