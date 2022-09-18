#include "grid.h"
#include <iostream>
#include "Screen.h"
#include "element.h"

Grid::Grid(Screen &srcScreen)
{
    mWidth = srcScreen.Width();
    mHeight = srcScreen.Height();
    mScreen = &srcScreen;
    gridData = new Element[mWidth * mHeight];
}

Grid::~Grid()
{
    delete[] gridData;
}

void Grid::Draw()
{

    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            mScreen->Draw(gridData[y * mWidth + x], x, y); // Drawing Element

            // gridData[y * mWidth + x].Render();
        }
    }
}

void Grid::SetElement(uint32_t x, uint32_t y, Element &elm)
{
    gridData[y * mWidth + x] = elm;
}