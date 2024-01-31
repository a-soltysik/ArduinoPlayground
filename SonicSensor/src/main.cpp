#include <Arduino.h>
#include "SonicSensor.h"

constexpr uint8_t TRIGGER = 12;
constexpr uint8_t ECHO = 11;

SonicSensor sonicSensor{TRIGGER, ECHO};

void setup() {
    Serial.begin(9600);
    delay(1000);
}

void loop() {
    Serial.print(sonicSensor.measureDistance());
    Serial.println(" mm");
    delay(1000);
}