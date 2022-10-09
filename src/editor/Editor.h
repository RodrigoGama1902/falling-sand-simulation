#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "Simulation.h"
#include "ToolHandler.h"
#include "Pencil.h"
#include "Brush.h"

#include "Element.h"

class Editor
{
public:
    Editor(Simulation *simulation);
    ~Editor();

    void SetActiveElement(Element *element) { activeElement = element; }
    Element *GetActiveElement() { return activeElement; }

    Brush *GetBrush() { return mBrush; }
    Pencil *GetPencil() { return mPencil; }
    ToolHandler *GetToolHandler() { return mToolHandler; }

private:
    Simulation *mSimulation;
    ToolHandler *mToolHandler;

    Element *activeElement;

    Pencil *mPencil;
    Brush *mBrush;
};

#endif