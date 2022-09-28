#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "element.h"
#include "grid.h"
#include "Screen.h"

class Brush
{
public:
    Brush(Grid *grid, Element &defaultElement);

    void Draw(uint32_t x, uint32_t y);
    void FillElement(const std::vector<Vec2D> &points);
    void DrawElementCircle(const Circle &circle);

    void DrawCursor(Screen &screen, uint32_t x, uint32_t y);

    void ToggleDraw(bool toggle);
    void SetElement(Element &elm);

    bool is_drawing() { return drawing; };

    void SetBrushSize(int size) { brush_size = size; };
    int GetBrushSize() { return brush_size; };

private:
    bool drawing = false;
    int brush_size = 5;

    int last_x_pos;
    int last_y_pos;

    Element *mElement;
    Grid *mGrid;
};

#endif