#include <Arduino.h>

#include "Digits.h"

constexpr uint8_t potentiometer = A0;
constexpr uint8_t latchPin = 11;
constexpr uint8_t clockPin = 9;
constexpr uint8_t dataPin = 12;
constexpr uint8_t oePin = 3;

void setup()
{
    Serial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(potentiometer, INPUT);
    analogWrite(oePin, 200);
}

void updateShiftRegister(uint8_t data)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float clamp(float value, float minV, float maxV)
{
    return min(max(value, minV), maxV);
}

float deadZoneClampedLerp(float value, float valueMax, float min, float minDeadZone, float max, float maxDeadZone)
{
    return clamp(lerp(min, max, (value - valueMax * maxDeadZone) / (valueMax * (1 - maxDeadZone - minDeadZone))),
                 min,
                 max);
}

void loop()
{
    constexpr float minDeadZone = 0.1F;
    constexpr float maxDeadZone = 0.0F;
    constexpr float maxValue = 1023.F;
    const uint32_t digit = deadZoneClampedLerp(analogRead(potentiometer),
                                               maxValue,
                                               0,
                                               minDeadZone,
                                               digits::digits.size() - 1,
                                               maxDeadZone);

    updateShiftRegister(digits::digits[digit]);
}
