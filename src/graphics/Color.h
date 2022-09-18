#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>

struct SDL_PixelFormat; // Forward declaration, SDL_PixelFormat is defined in SDL.h

class Color
{
    uint32_t mColor;

public:
    static const SDL_PixelFormat *mFormat;
    static void InitColorFormat(const SDL_PixelFormat *format);

    static Color Black() { return Color(0, 0, 0, 255); }
    static Color White() { return Color(255, 255, 255, 255); }
    static Color Red() { return Color(255, 0, 0, 255); }
    static Color Green() { return Color(0, 255, 0, 255); }
    static Color Blue() { return Color(0, 0, 255, 255); }
    static Color Yellow() { return Color(255, 255, 0, 255); }
    static Color Cyan() { return Color(0, 255, 255, 255); }

    Color() : Color(0){};
    Color(uint32_t color) : mColor(color){};
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    inline bool operator==(const Color &other) const { return mColor == other.mColor; }
    inline bool operator!=(const Color &other) const { return mColor != other.mColor; }

    inline uint32_t GetPixelColor() const { return mColor; }

    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void SetRed(uint8_t red);
    void SetGreen(uint8_t green);
    void SetBlue(uint8_t blue);
    void SetAlpha(uint8_t alpha);

    uint8_t GetRed() const;
    uint8_t GetGreen() const;
    uint8_t GetBlue() const;
    uint8_t GetAlpha() const;
};

#endif