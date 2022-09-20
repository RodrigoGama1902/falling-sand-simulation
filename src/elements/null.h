#ifndef _NULL_H_
#define _NULL_H_

#include "element.h"

class Null : public Element
{
public:
    Null();
    virtual void Update(Grid &grid, int x, int y) override;

    virtual Element *clone() const
    {
        return new Null(); // call the copy ctor.
    }
};

#endif
