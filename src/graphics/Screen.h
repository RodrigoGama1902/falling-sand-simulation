#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>
#include <vector>

#include "ScreenBuffer.h"
#include "graphics/Color.h"
#include "simulation/elements/base/Element.h"

class Vec2D;
class Line2D;
class Circle;

struct SDL_Window;
struct SDL_Surface;

class Screen
{
public:
    Screen();
    ~Screen();

    SDL_Window *Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreen(bool update = false);

    inline void SetClearColor(const Color &clearColor) { mClearColor = clearColor; }
    inline uint32_t Width() const { return mWidth; }
    inline uint32_t Height() const { return mHeight; }

    // Draw methods
    void Draw(int x, int y, const Color &color);
    void Draw(const Vec2D &point, const Color &color);

    // Element Draw
    void Draw(int x, int y, Element &elm);

    // Shape Drawing
    void Draw(const Line2D &line, const Color &color);
    void Draw(const Circle &circle, const Color &color);

private:
    Screen(const Screen &src);            // Disable copy constructor, that's why it's private
    Screen &operator=(const Screen &rhs); // Disable assignment operator, that's why it's private

    void ClearScreen();
    void FillPoly(const std::vector<Vec2D> &points, const Color &color);

    uint32_t mWidth;
    uint32_t mHeight;

    Color mClearColor;
    ScreenBuffer mBackBuffer;

    SDL_Window *moptrWindow;
    SDL_Surface *mnoptrWindowSurface;
};

#endif