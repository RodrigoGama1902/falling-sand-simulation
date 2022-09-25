#include "grid.h"
#include <iostream>
#include "Screen.h"
#include "element.h"
#include "sand.h"
#include "wall.h"

Grid::Grid(Screen &srcScreen) : Grid(srcScreen, new Sand(), 0)
{
}

Grid::Grid(Screen &mScreen, Element *elmFill, int fillPercent)
{
    mWidth = mScreen.Width();
    mHeight = mScreen.Height();
    this->mScreen = &mScreen;

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
    // delete[] gridData;
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

void Grid::SetElement(uint32_t x, uint32_t y, Element *elm)
{
    if (x >= mWidth || y >= mHeight)
    {
        return;
    }

    gridDataNext[x][y] = elm;
}

Element *Grid::GetElement(uint32_t x, uint32_t y)
{
    if (x < 0 || y < 0 || x >= mWidth || y >= mHeight)
    {
        return new Wall();
    }

    return gridDataNext[x][y];
}

void Grid::SwapGrids()
{
    gridData = gridDataNext;
}