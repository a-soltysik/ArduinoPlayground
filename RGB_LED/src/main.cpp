#include <Arduino.h>
#include "ColorConverter.h"

constexpr uint8_t RED = 3;
constexpr uint8_t GREEN = 5;
constexpr uint8_t BLUE = 6;

constexpr float SATURATION = 1.F;
constexpr float COLOR_VALUE = 0.05F;

constexpr float MAX_HUE = 360.F;
constexpr float HUE_PER_TICK = 0.005F;

HSV currentColor = {0, SATURATION, COLOR_VALUE};

void setup() {
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
}

void loop() {
    currentColor.hue += HUE_PER_TICK;
    if (currentColor.hue > MAX_HUE)
    {
        currentColor.hue = 0;
    }

    RGB color = HSVtoRGB(currentColor);

    analogWrite(RED, color.red);
    analogWrite(GREEN, color.green);
    analogWrite(BLUE, color.blue);
}
