#ifndef _TOOL_HANDLER_H_
#define _TOOL_HANDLER_H_

#include "PaintTool.h"
#include "element.h"

class ToolHandler
{
public:
    ToolHandler(PaintTool &defaultTool);
    ~ToolHandler();

    void SetTool(PaintTool *tool) { mTool = tool; };
    PaintTool *GetTool() { return mTool; };

private:
    PaintTool *mTool;
    Element *mElement;
};

#endif