#pragma once


struct RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct HSV
{
    float hue;
    float saturation;
    float value;
};

RGB HSVtoRGB(const HSV& hsv);
