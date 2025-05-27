#include "sensor_tsl2591.h"
#include "sensor_bme280.h"
#include "sensor_sgp30.h"

class Sensor {
    public:
        float Temp;
        float Humidity;

        void setup() {
            // BME280 Temp Sensor
            sensor_bme280_setup();
            
            // TSL2591 Lux Sensor
            sensor_2591_setup();
            sensor_2591_displayDetails();
            sensor_2591_configure();

            // SGP30 AQM Sensor
            sensor_sgp30_setup();
        }

        void measure() {
            this->Temp = sensor_bme280_getTemp();
            this->Humidity = sensor_bme280_getHumidity();
        }
};