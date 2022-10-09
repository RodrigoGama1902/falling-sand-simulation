#ifndef _TOOL_HANDLER_H_
#define _TOOL_HANDLER_H_

#include "editor/tools/PaintTool.h"
#include "simulation/elements/base/Element.h"

class ToolHandler
{
public:
    ToolHandler();
    ToolHandler(PaintTool &defaultTool);
    ~ToolHandler();

    void SetTool(PaintTool *tool) { mTool = tool; };
    PaintTool *GetTool() { return mTool; };

private:
    PaintTool *mTool;
    Element *mElement;
};

#endif