#ifndef _BRUSH_H_
#define _BRUSH_H_

#include "element.h"
#include "grid.h"
#include "Screen.h"

#include "PaintTool.h"

class Brush : public PaintTool
{
public:
    Brush(Grid *grid, Element &defaultElement);
    virtual ~Brush();

    virtual void Draw(uint32_t x, uint32_t y) override;
    virtual void DrawCursor(Screen &screen, uint32_t x, uint32_t y) override;

    void DrawElementCircle(const Circle &circle);
    void SetBrushSize(int size) { brush_size = size; };
    int GetBrushSize() { return brush_size; };

protected:
    int brush_size = 5;
};

#endif