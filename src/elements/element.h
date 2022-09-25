#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "Color.h"

struct Grid;

class Element
{
public:
    Element();

    virtual void Update(Grid &grid, int x, int y) = 0;
    virtual Element *clone() const = 0;

    Color elmColor;
    Color elmMinColor;
    Color elmMaxColor;

    int elmColorFadeFrequency;
    int currentColorFadeFrequency;

    int x_direction;

    bool solid;
    int density;
    bool moving;
};

#endif