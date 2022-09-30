#ifndef _PENCIL_H_
#define _PENCIL_H_

#include "PaintTool.h"

class Pencil : public PaintTool
{
public:
    Pencil(Grid *grid, Element &defaultElement);
    virtual ~Pencil();

    virtual void Draw(uint32_t x, uint32_t y, Element *elm) override;
    virtual void DrawCursor(Screen &screen, uint32_t x, uint32_t y) override;
};

#endif