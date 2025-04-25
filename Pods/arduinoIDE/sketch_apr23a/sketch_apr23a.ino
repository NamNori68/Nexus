#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#define LED_GPIO 2

int sda_pin = 5;
int scl_pin = 6;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

unsigned long delayTime;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_GPIO, OUTPUT);

  Wire.setPins(sda_pin, scl_pin);
  Wire.begin();

  unsigned status;
    
  // default settings
  //status = bme.begin();  
  // You can also pass in a Wire library object like &Wire2
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
  
  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" °F");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() * 0.02953 / 100.0F);
  Serial.println(" in Hg");

  Serial.print("Approx. Altitude = ");
  Serial.print(3.28 * bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" ft");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void loop() 
{
  digitalWrite(LED_GPIO, HIGH);
  delay(1000);
  digitalWrite(LED_GPIO, LOW);
  delay(1000);

  printValues();
  delay(1000);//delayTime);
}
