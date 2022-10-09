#include "SDL2/SDL.h"

#include "graphics/Color.h"
#include "graphics/Screen.h"

#include "utils/Utils.h"
#include "utils/Vec2D.h"

#include "shapes/Circle.h"
#include "shapes/Line2D.h"

#include "simulation/elements/base/Element.h"

#include <ctime>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <random>

Screen::Screen() : mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr)
{
}

Screen::~Screen()
{
    if (moptrWindow)
    {
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }

    SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{

    // Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    mWidth = w;
    mHeight = h;
    mMag = mag;

    // Create a window

    moptrWindow = SDL_CreateWindow("Arcade",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   mWidth * mag,
                                   mHeight * mag,
                                   SDL_WINDOW_SHOWN);

    if (moptrWindow)
    {
        // Create a renderer

        mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
        SDL_PixelFormat *pixelFormat = mnoptrWindowSurface->format;

        Color::InitColorFormat(pixelFormat); // Initialize color format, so it will be the same as the window surface

        mClearColor = Color::Black();

        mBackBuffer.Init(pixelFormat->format, mWidth, mHeight); // Initialize screen buffer
        mBackBuffer.Clear(mClearColor);
    }

    return moptrWindow;
}

void Screen::SwapScreen(bool update)
{
    assert(moptrWindow);
    if (moptrWindow)
    {
        if (!update) // If we don't want to update the screen pixels, just clear it
            ClearScreen();

        SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr); // Blit the created screenBuffer pixels to the window surface
        SDL_UpdateWindowSurface(moptrWindow);                                            // Update the window surface so the changed pixels will be shown

        if (!update)
            mBackBuffer.Clear(mClearColor); // Clear the screen buffer
    }
}

void Screen::Draw(int x, int y, const Color &color)

{
    /*
    assert(moptrWindow);
    if (moptrWindow)
    {

    }*/

    mBackBuffer.SetPixel(color, x, y);
}

void Screen::Draw(const Vec2D &point, const Color &color)
{
    mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
}

void Screen::Draw(const Line2D &line, const Color &color)
{
    int dx, dy;

    int x0 = roundf(line.GetP0().GetX());
    int y0 = roundf(line.GetP0().GetY());
    int x1 = roundf(line.GetP1().GetX());
    int y1 = roundf(line.GetP1().GetY());

    dx = x1 - x0;
    dy = y1 - y0;

    signed const char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1
    signed const char iy((dy > 0) - (dy < 0));

    dx = abs(dx) * 2;
    dy = abs(dy) * 2;

    Draw(x0, y0, color);

    if (dx >= dy) // go along x
    {
        int d = dy - dx / 2;

        while (x0 != x1) // keep looping along x until x0 is equal to the x1 (the end point x)
        {
            if (d >= 0) // if d is greater than 0, then we need to move along y (Get to the upper or lower pixel)
            {
                d -= dx;
                y0 += iy;
            }

            d += dy;
            x0 += ix; // move along x

            Draw(x0, y0, color);
        }
    }
    else // go along y
    {
        int d = dx - dy / 2;

        while (y0 != y1)
        {
            if (d >= 0)
            {
                d -= dy;
                x0 += ix;
            }
            d += dx;
            y0 += iy;

            Draw(x0, y0, color);
        }
    }
}

void Screen::Draw(int x, int y, Element &elm)
{
    mBackBuffer.SetPixel(elm.elmColor, x, y);
}

void Screen::Draw(const Circle &circle, const Color &color)
{
    static unsigned int NUM_CIRCLE_SEGMENTS = 64;

    float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vec2D p1 = p0;

    Line2D nextLineToDraw;

    for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; i++)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP0(p0);
        nextLineToDraw.SetP1(p1);

        Draw(nextLineToDraw, color);
        p0 = p1;
    }
}

void Screen::ClearScreen()
{
    SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor()); // Fill the window surface with the clear color
}

void Screen::FillPoly(const std::vector<Vec2D> &points, const Color &color)
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
                        Draw(pixelX, pixelY, color);
                    }
                }
            }
        }
    }
}
