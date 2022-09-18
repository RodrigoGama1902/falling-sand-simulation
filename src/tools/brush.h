#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "element.h"
#include "grid.h"

class Brush
{
public:
    Brush(Grid *grid);
    ~Brush();

    void Draw(int x, int y);

    Element *currentElement;

private:
    int last_x_pos;
    int last_y_pos;

    Grid *mGrid;
};

#endif