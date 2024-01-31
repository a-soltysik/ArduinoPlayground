#include "SonicSensor.h"
#include <Arduino.h>

constexpr uint32_t MIN_DELAY = 10;
constexpr uint32_t MIN_MEASUREMENT_DELAY = 50;

SonicSensor::SonicSensor(uint8_t triggerPin, uint8_t echoPin)
    : _triggerPin{triggerPin},
    _echoPin{echoPin}
{
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

uint32_t SonicSensor::waitForMinimumDelay() const
{
    const auto currentTime = micros();
    const auto deltaTime = currentTime - _lastTime;
    if (deltaTime < MIN_MEASUREMENT_DELAY)
    {
        delay(MIN_MEASUREMENT_DELAY - deltaTime);
    }
    return currentTime;
}

uint32_t SonicSensor::measureDistance() {
    _lastTime = waitForMinimumDelay();
    emitWave();
    const auto distance = microsecondsToMillimeters(waitForWave());

    if (distance > MAX_RANGE)
    {
        return UINT32_MAX;
    }
    if (distance < MIN_RANGE)
    {
        return 0;
    }
    return distance;
}

void SonicSensor::emitWave() const {
    digitalWrite(_triggerPin, LOW);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(MIN_DELAY);
    digitalWrite(_triggerPin, LOW);
}

uint32_t SonicSensor::waitForWave() const {
    return pulseIn(_echoPin, HIGH, millimetersToMicroseconds(MAX_RANGE * 105 / 100));
}
