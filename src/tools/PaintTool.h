#ifndef _PAINT_TOOL_H_
#define _PAINT_TOOL_H_

#include <stdint.h>
#include <vector>

#include "Vec2D.h"
#include "Grid.h"
#include "Screen.h"
#include "Element.h"

class Element;
class Screen;
class Grid;

class PaintTool
{
public:
    PaintTool(Grid *grid, Element &defaultElement);
    virtual ~PaintTool();

    virtual void Draw(uint32_t x, uint32_t y, Element *elm) = 0;
    virtual void DrawCursor(Screen &screen, uint32_t x, uint32_t y) = 0;

    void FillElement(const std::vector<Vec2D> &points, Element *elm);

    void ToggleDraw(bool toggle);
    void SetErasing(bool set_bool) { erasing = set_bool; }

    bool is_drawing() { return drawing; };

protected:
    bool drawing = false;
    bool erasing = false;

    int last_x_pos;
    int last_y_pos;

    Color cursorColor;
    Grid *mGrid;
};

#endif