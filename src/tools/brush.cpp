#include "brush.h"
#include "element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "grid.h"
#include "sand.h"
#include "Utils.h"
#include <algorithm>

#include "Circle.h"
#include "Screen.h"

Brush::Brush(Grid *grid)
{
    mElement = nullptr;
    mGrid = grid;
    last_x_pos = -1;
    last_y_pos = -1;
}

void Brush::Draw(uint32_t x, uint32_t y)
{
    if (!drawing)
    {
        return;
    }

    Circle elmCircle = Circle(Vec2D(x, y), brush_size);
    DrawElementCircle(elmCircle);

    // mGrid->SetElement(x, y, *mElement); // this will not create a new instance of the element, but will instead just copy the pointer to the element,
    //   optimized for performance, but colors cannot be instantiated.

    last_x_pos = x;
    last_y_pos = y;
}

void Brush::DrawCursor(Screen &screen, uint32_t x, uint32_t y)
{
    Circle circle(Vec2D(x, y), brush_size);
    Color whiteColor = Color::White();
    screen.Draw(circle, whiteColor);
}

void Brush::ToggleDraw(bool toggle)
{
    if (toggle)
    {
        drawing = true;
    }
    else
    {
        last_x_pos = -1;
        last_y_pos = -1;
        drawing = false;
    }
}

void Brush::SetElement(Element &elm)
{
    mElement = &elm;
}

void Brush::DrawElementCircle(const Circle &circle)
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

    FillElement(circlePoints);
}

void Brush::FillElement(const std::vector<Vec2D> &points)
{
    if (points.size() > 0)
    {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float left = points[0].GetX();
        float right = points[0].GetX();

        for (size_t i = 1; i < points.size(); i++)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }
            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }
            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }
            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
        }

        for (int pixelY = top; pixelY < bottom; pixelY++)
        {
            std::vector<float> nodeXVec;

            size_t j = points.size() - 1;

            for (size_t i = 0; i < points.size(); i++)
            {
                float pointIY = points[i].GetY();
                float pointJY = points[j].GetY();

                if ((pointIY <= (float)pixelY && pointJY > (float)pixelY) || (pointJY <= (float)pixelY && pointIY > (float)pixelY))
                {
                    float denom = pointJY - pointIY;
                    if (is_equal(denom, 0.0f))
                    {
                        continue;
                    }

                    float x = points[i].GetX() + ((float)pixelY - pointIY) / denom * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }

                j = i;
            }

            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<float>());

            for (size_t i = 0; i < nodeXVec.size(); i += 2)
            {
                if (nodeXVec[i] > right)
                {
                    break;
                }

                if (nodeXVec[i + 1] > left)
                {
                    if (nodeXVec[i] < left)
                    {
                        nodeXVec[i] = left;
                    }
                    if (nodeXVec[i + 1] > right)
                    {
                        nodeXVec[i + 1] = right;
                    }

                    for (int pixelX = nodeXVec[i]; pixelX < nodeXVec[i + 1]; pixelX++)
                    {
                        if (mGrid->GetElement(pixelX, pixelY) == nullptr)
                            mGrid->SetElement(pixelX, pixelY, mElement->clone());
                    }
                }
            }
        }
    }
}
