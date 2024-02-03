#include <Arduino.h>

constexpr uint8_t X_PIN = A0;
constexpr uint8_t Y_PIN = A1;
constexpr uint8_t SWITCH = 2;

void setup() {
    pinMode(SWITCH, INPUT_PULLUP);
    Serial.begin(9600);
}

float analogToUnit(uint16_t analog)
{
    return static_cast<float>(analog) / 512.F - 1.F;
}

void loop() {
    Serial.print("x: ");
    Serial.print(analogToUnit(analogRead(X_PIN)));
    Serial.print("; y: ");
    Serial.print(analogToUnit(analogRead(Y_PIN)));
    Serial.print("; switch: ");
    Serial.print(!digitalRead(SWITCH));
    Serial.println();
    delay(500);
}