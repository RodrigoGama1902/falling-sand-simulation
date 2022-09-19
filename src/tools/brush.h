#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "element.h"
#include "grid.h"

class Brush
{
public:
    Brush(Grid *grid);

    void Draw(uint32_t x, uint32_t y);
    void ToggleDraw(bool toggle);
    void SetElement(Element &elm);

    bool is_drawing() { return drawing; };

private:
    bool drawing = false;
    int last_x_pos;
    int last_y_pos;

    Element *mElement;
    Grid *mGrid;
};

#endif