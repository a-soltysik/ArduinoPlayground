#pragma once

#include <inttypes.h>

class SonicSensor
{
public:
    static constexpr uint32_t MAX_RANGE = 4000;
    static constexpr uint32_t MIN_RANGE = 20;

    SonicSensor(uint8_t triggerPin, uint8_t echoPin);

    uint32_t measureDistance();

private:
    static constexpr uint32_t WAVE_LENGTH = 58;
    static constexpr uint32_t millimetersToMicroseconds(uint32_t millimeters)
    {
        return millimeters * WAVE_LENGTH / 10;
    }

    static constexpr uint32_t microsecondsToMillimeters(uint32_t microseconds)
    {
        return microseconds * 10 / WAVE_LENGTH;
    }

    uint32_t waitForMinimumDelay() const;
    void emitWave() const;
    uint32_t waitForWave() const;

    uint8_t _triggerPin;
    uint8_t _echoPin;
    uint32_t _lastTime = 0;
};