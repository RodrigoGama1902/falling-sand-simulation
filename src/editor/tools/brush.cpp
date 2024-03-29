#include "SDL2/SDL.h"

#include "editor/tools/brush.h"
#include "editor/tools/PaintTool.h"

#include "simulation/elements/base/Element.h"
#include "simulation/Grid.h"
#include "simulation/elements/base/Solid.h"

#include "graphics/Screen.h"
#include "graphics/Color.h"
#include "graphics/Screen.h"

#include "shapes/Line2D.h"
#include "shapes/Circle.h"

#include "utils/Utils.h"

#include <algorithm>

Brush::Brush(Grid *grid, Element &defaultElement) : PaintTool(grid, defaultElement)
{
}

Brush::~Brush()
{
}

void Brush::Draw(uint32_t x, uint32_t y, Element *elm)
{
    if (is_drawing())
    {
        Circle elmCircle = Circle(Vec2D(x, y), brush_size);
        DrawElementCircle(elmCircle, elm);

        last_x_pos = x;
        last_y_pos = y;
    }
}

void Brush::DrawCursor(Screen &screen, uint32_t x, uint32_t y)
{
    Circle circle(Vec2D(x, y), brush_size);
    screen.Draw(circle, cursorColor);
}

void Brush::DrawElementCircle(const Circle &circle, Element *elm)
{
    static unsigned int NUM_CIRCLE_SEGMENTS = 32;

    std::vector<Vec2D> circlePoints;
    std::vector<Line2D> lines;

    float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vec2D p1 = p0;

    Line2D nextLineToDraw;

    for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; i++)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP0(p0);
        nextLineToDraw.SetP1(p1);

        lines.push_back(nextLineToDraw);
        p0 = p1;
        circlePoints.push_back(p0);
    }

    FillElement(circlePoints, elm);
}
