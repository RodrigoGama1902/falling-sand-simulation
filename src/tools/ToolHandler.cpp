#include "ToolHandler.h"

ToolHandler::ToolHandler(PaintTool &defaultTool)
{
    mTool = &defaultTool;
}

ToolHandler::~ToolHandler()
{
}