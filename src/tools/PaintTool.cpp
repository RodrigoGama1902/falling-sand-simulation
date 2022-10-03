#include "PaintTool.h"

#include "Element.h"
#include "SDL2/SDL.h"
#include "Screen.h"
#include "Color.h"
#include "Line2D.h"
#include "Grid.h"
#include "Solid.h"
#include "Utils.h"
#include <algorithm>

#include "Circle.h"
#include "Screen.h"

PaintTool::PaintTool(Grid *grid, Element &defaultElement)
{
    mGrid = grid;
    cursorColor = Color::White();
    last_x_pos = -1;
    last_y_pos = -1;
}

PaintTool::~PaintTool()
{
}

void PaintTool::ToggleDraw(bool toggle)
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

void PaintTool::FillElement(const std::vector<Vec2D> &points, Element *elm)
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
                        if (erasing)
                        {
                            mGrid->RemoveElement(pixelX, pixelY);
                        }
                        else
                        {
                            if (mGrid->GetElement(pixelX, pixelY) == nullptr)
                            {
                                if (rand() % 100 < elm->spawn_probability)
                                {
                                    mGrid->SetElement(pixelX, pixelY, elm->clone());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
