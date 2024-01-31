#include <Arduino.h>
#include <Servo.h>

Servo servo;
constexpr uint8_t SERVO = 9;

void setup() {
    Serial.begin(9600);
    servo.attach(SERVO);
}

void loop() {
    for (uint32_t position = 0; position <= 180; position++) {
        servo.write(position);
        delay(50);
    }
    for (uint32_t position = 180; position-- > 0;) {
        servo.write(position);
        delay(50);
    }
}

