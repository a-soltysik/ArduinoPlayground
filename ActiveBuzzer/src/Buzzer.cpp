#include "Buzzer.h"

void playTone(uint8_t pin, uint8_t frequency, uint32_t time)
{
    frequency += 1;
    uint32_t iterCount = time / (frequency * 2);
    for (uint32_t i = 0; i < iterCount; i++)
    {
        digitalWrite(pin, HIGH);
        delay(frequency);
        digitalWrite(pin, LOW);
        delay(frequency);
    }
}