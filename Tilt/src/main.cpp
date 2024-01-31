#include <Arduino.h>

constexpr uint8_t TILT = 2;
constexpr uint8_t BUZZER = 3;

void setup()
{
    pinMode(BUZZER, OUTPUT);
    pinMode(TILT,INPUT);

    digitalWrite(TILT, HIGH);
}

void loop()
{
    if(digitalRead(TILT) == HIGH)
    {
        digitalWrite(BUZZER, HIGH);
    }
    else
    {
        digitalWrite(BUZZER, LOW);
    }
}