#include <Arduino.h>
#include <ArduinoJson.h>
#include <stdexcept>
#include <iostream>
#include <time.h>
#include <Wire.h>
#include <WiFi.h>
#include "sensor_tsl2591.h"
#include "sensor_bme280.h"
#include "sensor_sgp30.h"
#include "sensor.h"

#define LED_GPIO 2

using namespace std;

const char* ssid = "Draedus";
const char* password = "Enterprise65";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -28800; //3600;
const int daylightOffset_sec = 3600;

//IC2 Pin definition for ESP30 board
int scl_pin = 7;
int sda_pin = 8;

Sensor _sensor;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_GPIO, OUTPUT);

  Wire.setPins(sda_pin, scl_pin);
  Wire.begin();

  _sensor.setup();

  // BME280 Temp Sensor
  //sensor_bme280_setup();
  
  // TSL2591 Lux Sensor
  //sensor_2591_setup();
  //sensor_2591_displayDetails();
  //sensor_2591_configure();

  // SGP30 AQM Sensor
  //sensor_sgp30_setup();

  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  delay(100);

  WiFi.setHostname("Nexus ESP32 Pod");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    delay(1000);
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.println(WiFi.localIP());
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
  //digitalWrite(LED_GPIO, HIGH);
  //delay(1000);
  //digitalWrite(LED_GPIO, LOW);
  //delay(1000);
  print_time();

  try
  {
    _sensor.measure();
    // BMD280 Sensor Read
    sensor_bme280_measure();

    // 2591 Sensor Read
    sensor_2591_advancedMeasure();

    // SGP30 AQM Sensor Read0
    sensor_sgp30_measure();
    
    JsonDocument doc;

    doc["sensor"] = "BME280";
    //doc["time"] = &timeinfo, "%A, %B %d %Y %H:%M:%S";
    doc["Temperature"] = _sensor.Temp;
    doc["Humidity"] = _sensor.Humidity;

    serializeJson(doc, Serial);
  }
  catch(invalid_argument& e)
  {
    cerr << e.what() << '\n';
    return;
  }
  
  Serial.println();
  delay(60000);
}

