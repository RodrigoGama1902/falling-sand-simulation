#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "element.h"
#include "grid.h"

class Brush
{
public:
    Brush(Grid *grid);

    void Draw(uint32_t x, uint32_t y, Element &elm);
    void ToggleDraw(bool toggle);
    bool is_drawing() { return drawing; };

    Element *currentElement;

private:
    bool drawing = false;
    int last_x_pos;
    int last_y_pos;
    Grid *mGrid;
};

#endif