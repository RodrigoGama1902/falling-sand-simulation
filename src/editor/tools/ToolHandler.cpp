#include "editor/tools/ToolHandler.h"

ToolHandler::ToolHandler(PaintTool &defaultTool)
{
    mTool = &defaultTool;
}

ToolHandler::~ToolHandler()
{
}