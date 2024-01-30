#include <Arduino.h>
#include "Buzzer.h"

constexpr uint8_t BUZZER = 12;
constexpr uint8_t ON_SWITCH = 6;
constexpr uint8_t OFF_SWITCH = 5;
constexpr uint32_t MAX_FREQUENCY = 10;
constexpr uint32_t LENGTH = 250;

uint32_t frequency = 0;
int8_t direction = 1;
bool shouldPlay = false;

void setup() {
    pinMode(BUZZER, OUTPUT);
    pinMode(ON_SWITCH, INPUT_PULLUP);
    pinMode(OFF_SWITCH, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(ON_SWITCH) == LOW)
    {
        shouldPlay = true;
    }
    if (digitalRead(OFF_SWITCH) == LOW)
    {
        shouldPlay = false;
    }
    if (shouldPlay)
    {
        playTone(BUZZER, frequency, LENGTH);
        frequency += direction;

        if (frequency >= MAX_FREQUENCY || frequency <= 0)
        {
            direction *= -1;
        }
    }
    else
    {
        digitalWrite(BUZZER, LOW);
    }

}