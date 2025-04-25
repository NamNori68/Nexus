#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

float temp;
float humidity;

void sensor_bme280_setup(void)
{
    unsigned status;
    
    // default settings
    status = bme.begin(0x76, &Wire);
  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); 
        Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
}

void sensor_bme280_measure(void)
{
    temp = 1.8 * bme.readTemperature() + 32;
    humidity = bme.readHumidity();

    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println(" °F");

    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() * 0.02953 / 100.0F);
    Serial.println(" in Hg");
  
    Serial.print("Approx. Altitude = ");
    Serial.print(3.28 * bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" ft");
}