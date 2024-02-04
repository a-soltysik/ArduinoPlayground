#include <Arduino.h>

constexpr uint8_t latchPin = 11;
constexpr uint8_t clockPin = 9;
constexpr uint8_t dataPin = 12;
constexpr uint8_t potentiometer = A0;
constexpr uint8_t oePin = 3;

void updateShiftRegister(uint8_t data) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(potentiometer, INPUT);
    analogWrite(oePin, 254);
}

void loop() {
    uint8_t leds = 0;

    const auto read = 1023 - analogRead(potentiometer);
    const auto value = read / 128;
    for (uint8_t i = 0; i <= value; i++) {
        bitSet(leds, i);
    }
    for (uint8_t i = value + 1; i < 8; i++) {
        bitClear(leds, i);
    }
    updateShiftRegister(leds);
}

