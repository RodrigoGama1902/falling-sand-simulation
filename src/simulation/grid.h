#ifndef _GRID_H_
#define _GRID_H_

#include <stdint.h>
#include <vector>

/*

    Grid class

    This class is used to store and manage the elements in the simulation.

    It is also used to render the elements to the screen.

    The update method used is in this grid class is called the "odd-even" method.

    At the Grid Init, the odd_even_check variable is set to true,
    When an element is updated, it's odd_even_check variable is set to the same value as the Grid's odd_even_check variable.
    When the Grid is updated, it switches the odd_even_check variable, so when the update pointer finds the same element, it will be ignore.

    When all the grid was updated, the Grid switches the odd_even_check variable again, so the next update will update all the elements that are not
    the same as the switched odd_even_check value.

    After that the grid starts updating from the back to the finish, it solves the issue that the simulation will be balanced, both right to the left, and left to
    the right update.

*/

class Screen;
class Element;

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

    void DebugUpdate(bool skip_update_null_elements = true, bool full_grid_update = false);

    void Draw();
    void DrawDebuggerPointer(); // Draw the current cell being updated

    void Clear();

    Element *GetElement(uint32_t x, uint32_t y);

    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

    void SetIsPointerSkipping(bool toggle)
    {
        isPointerSkipping = toggle;
        show_debugger_pointer = true;
    };
    void SetIsPointerFullSkip(bool toggle)
    {
        isPointerFullSkip = toggle;
        show_debugger_pointer = false;
    };

    bool GetPointerSkipping() const { return isPointerSkipping; };
    bool GetPointerFullSkip() const { return isPointerFullSkip; };

    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }

    uint32_t GetDebugCurrentX() { return debugCurrentX; };
    uint32_t GetDebugCurrentY() { return debugCurrentY; };

    void SetShowDebuggerPointer(bool show) { show_debugger_pointer = show; }

private:
    bool odd_even_check;
    bool show_debugger_pointer;

    bool isPointerSkipping;
    bool isPointerFullSkip;

    uint32_t mWidth;
    uint32_t mHeight;

    Screen *mScreen;

    uint32_t debugCurrentX;
    uint32_t debugCurrentY;

    std::vector<std::vector<Element *>> gridData;
};

#endif