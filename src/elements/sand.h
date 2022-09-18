#ifndef _SAND_H_
#define _SAND_H_

#include "element.h"

class Sand : public Element
{
public:
    Sand();
    ~Sand();
    void Update();
    void Render();
};

#endif