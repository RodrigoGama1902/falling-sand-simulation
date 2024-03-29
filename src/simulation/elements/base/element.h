#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "graphics/Color.h"

struct Grid;

class Element
{
public:
    Element();
    virtual ~Element();

    virtual void UpdateColor() = 0;
    virtual void Move(Grid &grid, int x, int y) = 0;
    virtual void Update(Grid &grid, int x, int y) = 0;

    virtual Element *clone() const = 0;

    Color elmColor;
    Color elmMinColor;
    Color elmMaxColor;

    int x_direction;

    bool solid;
    int liquid_density;
    int velocity_y;
    int friction;

    bool moving;

    int spawn_probability;

    bool odd_even_check;
};

#endif