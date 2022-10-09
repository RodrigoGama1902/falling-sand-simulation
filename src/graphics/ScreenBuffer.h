#ifndef _SCREEN_BUFFER_H_
#define _SCREEN_BUFFER_H_
#include <stdint.h>
#include "graphics/Color.h"

struct SDL_Surface;

class ScreenBuffer
{
public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer &other);
    ~ScreenBuffer();

    ScreenBuffer &operator=(const ScreenBuffer &other);

    void Init(uint32_t format, uint32_t width, uint32_t height);

    inline SDL_Surface *GetSurface() { return mSurface; }

    void Clear(const Color &c = Color::Black());
    void SetPixel(const Color &color, int x, int y);

private:
    SDL_Surface *mSurface;
    uint32_t GetIndex(int r, int c);
};

#endif