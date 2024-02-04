#include <Arduino.h>
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

struct Coefficients
{
    float a;
    float b;
    float c;
};

struct Input
{
    float temperature;
    float resistance;
};

Coefficients calculateCoefficients(Input a, Input b, Input c)
{
    const float l1 = log(a.resistance);
    const float l2 = log(b.resistance);
    const float l3 = log(c.resistance);

    const float y1 = 1 / a.temperature;
    const float y2 = 1 / b.temperature;
    const float y3 = 1 / c.temperature;

    const float gamma2 = (y2 - y1) / (l2 - l1);
    const float gamma3 = (y3 - y1) / (l3 - l1);

    Coefficients result {};
    result.c = ((gamma3 - gamma2) / (l3 - l1)) / (l1 + l2 + l3);
    result.b = gamma2 - result.c * (l1 * l1 + l1 * l2 + l2 * l2);
    result.a = y1 - (result.b + l1 * l1 * result.c) * l1;

    return result;
}

float getTemperature(float A, float B, float C, float R)
{
    const float logR = log(R);
    return 1.F / (A + B * logR + C * (logR * logR * logR));
}

float getResistance(float R1, float vIn, float vOut)
{
    return R1 * (vIn / vOut - 1);
}

float getVoltage(uint32_t analogInput, float vIn)
{
    static constexpr float analogRange = 1024.F;
    return static_cast<float>(analogInput) / analogRange * vIn;
}

bool measureTemperatureDht(float& temperature, DHT_nonblocking& currentDht)
{
    static uint32_t lastMeasurement = millis();

    if (millis() - lastMeasurement > 3000)
    {
        float humidity {};
        if (currentDht.measure(&temperature, &humidity))
        {
            lastMeasurement = millis();
            return true;
        }
    }

    return false;
}

float error(float temperature, float masterTemperature)
{
    return abs(temperature - masterTemperature) / abs(masterTemperature);
}

constexpr uint8_t dhtSensorType = DHT_TYPE_11;
constexpr uint8_t dhtSensorPin = 2;
constexpr uint8_t thermistorPin = A0;

DHT_nonblocking dht {dhtSensorPin, dhtSensorType};
LiquidCrystal lcd {7, 8, 9, 10, 11, 12};
Coefficients coefficients = calculateCoefficients({0 + 273.15, 98960}, {20 + 273.15, 12510}, {60 + 273.15, 2476});

void setup()
{
    lcd.begin(16, 2);
}

void loop()
{
    static constexpr float V = 5;
    static constexpr float kelvin = 273.15F;

    lcd.setCursor(0, 0);
    const float vOut = getVoltage(analogRead(thermistorPin), V);
    lcd.print(vOut);
    lcd.print(" V");
    lcd.setCursor(0, 1);
    const float temperature =
        getTemperature(coefficients.a, coefficients.b, coefficients.c, getResistance(10000, V, vOut)) - kelvin;
    lcd.print(temperature);
    lcd.print(" C");

    float dhtTemperature {};
    if (measureTemperatureDht(dhtTemperature, dht))
    {
        lcd.setCursor(8, 0);
        lcd.print(dhtTemperature);
        lcd.print(" C");

        lcd.setCursor(8, 1);
        lcd.print(error(temperature + kelvin, dhtTemperature + kelvin) * 100);
        lcd.print(" %");
    }
}