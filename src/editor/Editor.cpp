#include "Editor.h"

Editor::Editor(Simulation *simulation)
{
    activeElement = simulation->sand_element;

    mPencil = new Pencil(simulation->GetGrid(), *simulation->sand_element);
    mBrush = new Brush(simulation->GetGrid(), *simulation->sand_element);
    mToolHandler = new ToolHandler(*mBrush);
}

Editor::~Editor()
{
}
