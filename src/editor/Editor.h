#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "simulation/Simulation.h"

#include "editor/tools/ToolHandler.h"
#include "editor/tools/Pencil.h"
#include "editor/tools/Brush.h"

#include "graphics/Screen.h"

#include "simulation/elements/base/Element.h"

class Editor
{
public:
    Editor(Simulation *simulation, Screen *screen);
    ~Editor();

    void Render();
    void Update();

    void SetActiveElement(Element *element) { activeElement = element; }
    Element *GetActiveElement() { return activeElement; }

    Brush *GetBrush() { return mBrush; }
    Pencil *GetPencil() { return mPencil; }
    ToolHandler *GetToolHandler() { return mToolHandler; }

private:
    Element *activeElement;
    Screen *mScreen;

    ToolHandler *mToolHandler;
    Pencil *mPencil;
    Brush *mBrush;
};

#endif