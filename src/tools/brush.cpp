#include "brush.h"
#include "Element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "Grid.h"
#include "Solid.h"
#include "Utils.h"
#include <algorithm>

#include "PaintTool.h"

#include "Circle.h"
#include "Screen.h"

Brush::Brush(Grid *grid, Element &defaultElement) : PaintTool(grid, defaultElement)
{
}

Brush::~Brush()
{
}

void Brush::Draw(uint32_t x, uint32_t y, Element *elm)
{
    Circle elmCircle = Circle(Vec2D(x, y), brush_size);
    DrawElementCircle(elmCircle, elm);

    last_x_pos = x;
    last_y_pos = y;
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
