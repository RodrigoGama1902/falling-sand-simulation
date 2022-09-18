#ifndef _GRID_H_
#define _GRID_H_

#include <stdint.h>
#include "element.h"
#include "Screen.h"

class Grid
{
public:
    Grid(Screen &mScreen);
    ~Grid();

    void SetElement(uint32_t x, uint32_t y, Element &elm);

    void Draw();

    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

private:
    uint32_t mWidth;
    uint32_t mHeight;

    Screen *mScreen;
    Element *gridData;
};

#endif