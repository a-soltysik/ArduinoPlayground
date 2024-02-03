#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

constexpr uint8_t DHT_SENSOR = 2;
DHT_nonblocking dht_sensor{DHT_SENSOR, DHT_SENSOR_TYPE};

void setup( )
{
    Serial.begin( 9600);
}

bool measureEnvironment(float& temperature, float& humidity )
{
    static uint32_t lastMeasurement = millis( );

    if(millis() - lastMeasurement  > 3000)
    {
        if(dht_sensor.measure(&temperature, &humidity))
        {
            lastMeasurement = millis( );
            return true;
        }
    }

    return false;
}

void loop( )
{
    float temperature;
    float humidity;

    if(measureEnvironment(temperature, humidity))
    {
        Serial.print( "T = " );
        Serial.print( temperature, 1 );
        Serial.print( " deg. C, H = " );
        Serial.print( humidity, 1 );
        Serial.println( "%" );
    }
}
