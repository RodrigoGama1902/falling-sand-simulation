#include "grid.h"
#include <iostream>
#include "Screen.h"
#include "element.h"
#include "null.h"

Grid::Grid(Screen &srcScreen)
{
    mWidth = srcScreen.Width();
    mHeight = srcScreen.Height();
    mScreen = &srcScreen;
    gridData = std::vector<std::vector<Element *>>(mWidth, std::vector<Element *>(mHeight, new Null()));
    gridDataNext = std::vector<std::vector<Element *>>(mWidth, std::vector<Element *>(mHeight, new Null()));
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
            gridData[x][y]->Update(*this, x, y);
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
            mScreen->Draw(x, y, gridData[x][y]->elmColor);
        }
    }
}

void Grid::SetElement(uint32_t x, uint32_t y, Element &elm)
{
    gridDataNext[x][y] = &elm;
}

Element &Grid::GetElement(uint32_t x, uint32_t y)
{
    return *gridData[x][y];
}

void Grid::SwapGrids()
{
    gridData = gridDataNext;
}