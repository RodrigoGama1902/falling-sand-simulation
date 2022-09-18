#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "Color.h"

class Element
{
public:
    Element();

    virtual ~Element();
    virtual void Update();
    virtual void Render();

    Color elmColor;
};

#endif