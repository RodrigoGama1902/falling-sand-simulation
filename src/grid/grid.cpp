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
    gridData = new Null[mWidth * mHeight];
}

Grid::~Grid()
{
    delete[] gridData;
}

void Grid::Update()
{
    for (uint32_t y = 0; y < mHeight; y++)
    {
        for (uint32_t x = 0; x < mWidth; x++)
        {
            gridData[y * mWidth + x].Update(*this, x, y);
        }
    }
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

Element &Grid::GetElement(uint32_t x, uint32_t y)
{
    return gridData[y * mWidth + x];
}