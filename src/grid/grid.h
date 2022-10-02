#ifndef _GRID_H_
#define _GRID_H_

#include <stdint.h>
#include "Element.h"
#include "Screen.h"
#include <vector>

class Grid
{
public:
    Grid(Screen &mScreen);
    Grid(Screen &mScreen, bool debug);
    Grid(Screen &mScreen, Element *elmFill, int fillPercent);

    ~Grid();

    void SetElement(uint32_t x, uint32_t y, Element *elm);
    void RemoveElement(uint32_t x, uint32_t y);

    void SwapElements(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

    void Update();
    void DebugUpdate(bool fullSkip = false);

    void Draw();
    void Clear();

    Element *GetElement(uint32_t x, uint32_t y);

    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }

    uint32_t GetDebugCurrentX() { return debugCurrentX; };
    uint32_t GetDebugCurrentY() { return debugCurrentY; };

private:
    bool odd_even_check;

    uint32_t mWidth;
    uint32_t mHeight;

    Screen *mScreen;

    uint32_t debugCurrentX;
    uint32_t debugCurrentY;

    std::vector<std::vector<Element *>> gridData;
};

#endif