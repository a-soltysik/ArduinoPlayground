#include <Arduino.h>
#include "ColorConverter.h"

void getRawValue(const HSV& hsv, float& red, float& green, float& blue)
{
    float c = hsv.value * hsv.saturation;
    float x = c * static_cast<float>((1.F - fabs(fmod((hsv.hue / 60.F), 2) - 1)));

    if (hsv.hue < 60)
    {
        red = c;
        green = x;
        blue = 0;
    }
    else if (hsv.hue < 120)
    {
        red = x;
        green = c;
        blue = 0;
    }
    else if (hsv.hue < 180)
    {
        red = 0;
        green= c;
        blue = x;
    }
    else if(hsv.hue < 240)
    {
        red = 0;
        green = x;
        blue = c;
    }
    else if(hsv.hue < 300)
    {
        red = x;
        green = 0;
        blue = c;
    }
    else
    {
        red = c;
        green = 0;
        blue = x;
    }
}

RGB HSVtoRGB(const HSV& hsv)
{
    float r = 0.F;
    float g = 0.F;
    float b = 0.F;

    float c = hsv.value * hsv.saturation;
    float m = hsv.value - c;

    getRawValue(hsv, r, g, b);

    return {static_cast<uint8_t>((r + m) * 255.F), static_cast<uint8_t>((g + m) * 255.F), static_cast<uint8_t>((b + m) * 255.F)};
}