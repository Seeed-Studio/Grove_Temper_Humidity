/*
    Demo name   : TH06_dev demo
    Usage       : DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
    Author      : Oliver Wang from Seeed Studio
    Version     : V0.1
*/

#include <TH06_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"

#define ShowSerial Serial

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial Serial
    #define ShowSerial Serial
    TH06_dev TH06;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define COMSerial Serial1
#define ShowSerial SerialUSB
TH06_dev TH06;
#endif

#ifdef ARDUINO_ARCH_STM32F4
#define COMSerial Serial
#define ShowSerial SerialUSB
TH06_dev TH06;
#endif


void setup() {
  ShowSerial.begin(9600);        // start serial for output

  ShowSerial.println("****TH06_dev demo by seeed studio****\n");
  /* Reset HP20x_dev */
  TH06.begin();

  /* Determine TH02_dev is available or not */
  ShowSerial.println("TH06_dev is available.\n");
}


void loop() {
  float temper = TH06.ReadTemperature();
  ShowSerial.print("Temperature: ");
  ShowSerial.print(temper);
  ShowSerial.println("C\r\n");
  //Serial.print("%\t");

  float humidity = TH06.ReadHumidity();
  ShowSerial.print("Humidity: ");
  ShowSerial.print(humidity);
  ShowSerial.println("%\r\n");
  delay(1000);
}
