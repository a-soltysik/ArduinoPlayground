#include <Arduino.h>

constexpr uint8_t A_BUTTON = 9;
constexpr uint8_t B_BUTTON = 8;
constexpr uint8_t LED = 5;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(A_BUTTON, INPUT_PULLUP);
    pinMode(B_BUTTON, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(A_BUTTON) == LOW)
    {
        digitalWrite(LED, HIGH);
    }
    if (digitalRead(B_BUTTON) == LOW)
    {
        digitalWrite(LED, LOW);
    }
}