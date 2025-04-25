#include <Arduino.h>
#include <time.h>
#include <Wire.h>
#include <WiFi.h>
#include "sensor_tsl2591.h"
#include "sensor_bme280.h"
#include "sensor_sgp30.h"

#define LED_GPIO 2

//IC2 Pin definition for ESP30 board
int scl_pin = 7;
int sda_pin = 8;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_GPIO, OUTPUT);

  Wire.setPins(sda_pin, scl_pin);
  Wire.begin();

  // BME280 Temp Sensor
  sensor_bme280_setup();
  
  // TSL2591 Lux Sensor
  sensor_2591_setup();
  sensor_2591_displayDetails();
  sensor_2591_configure();

  // SGP30 AQM Sensor
  sensor_sgp30_setup();
}

void print_time() 
{
  time_t now;
  struct tm *local_time_info;
  struct timeval tv;
  char time_buffer[80];

  gettimeofday(&tv, NULL);
  now = tv.tv_sec;

  local_time_info = localtime(&now);

  if (local_time_info == NULL) {
      perror("localtime");
      return;
  }

  strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", local_time_info);
  printf("Local time: %s\n", time_buffer);
}

void loop() 
{
  //Serial.println("Guten Tag, Wald");
  digitalWrite(LED_GPIO, HIGH);
  delay(1000);
  digitalWrite(LED_GPIO, LOW);
  delay(1000);

  print_time();

  // BMD280 Sensor Read
  sensor_bme280_measure();

  // 2591 Sensor Read
  sensor_2591_advancedMeasure();

  // SGP30 AQM Sensor Read0
  sensor_sgp30_measure();

  Serial.println();
  delay(2500);//delayTime);
}

