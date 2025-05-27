#ifndef CODE_INCLUDE_SENSOR_BME280_H_
#define CODE_INCLUDE_SENSOR_BME280_H_

void sensor_bme280_setup(void);

void sensor_bme280_measure(void);

float sensor_bme280_getTemp(void);

float sensor_bme280_getHumidity(void);

#endif
