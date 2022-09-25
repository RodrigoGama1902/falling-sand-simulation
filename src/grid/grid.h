#ifndef _GRID_H_
#define _GRID_H_

#include <stdint.h>
#include "element.h"
#include "Screen.h"
#include <vector>

class Grid
{
public:
    Grid(Screen &mScreen);
    Grid(Screen &mScreen, Element *elmFill, int fillPercent);

    ~Grid();

    void SetElement(uint32_t x, uint32_t y, Element *elm);
    void Update();
    void Draw();
    void SwapGrids();

    Element *GetElement(uint32_t x, uint32_t y);

    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }

private:
    uint32_t mWidth;
    uint32_t mHeight;

    Screen *mScreen;

    std::vector<std::vector<Element *>> gridData;
    std::vector<std::vector<Element *>> gridDataNext;
};

#endif