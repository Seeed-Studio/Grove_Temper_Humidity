/*
    Demo name   : TH02_dev demo
    Usage       : DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
    Author      : Oliver Wang from Seeed Studio
    Version     : V0.1
*/

#include <TH02_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"

#define ShowSerial Serial
#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial Serial
    #define ShowSerial Serial
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define COMSerial Serial1
    #define ShowSerial Serial
#endif

#ifdef ARDUINO_ARCH_STM32F4
    #define COMSerial Serial
    #define ShowSerial SerialUSB
#endif

TH02_dev TH02;

void setup() {
    ShowSerial.begin(9600);        // start serial for output

    ShowSerial.println("****TH02_dev demo by seeed studio****\n");
    /* Power up,delay 150ms,until voltage is stable */
    delay(150);
    /* Reset HP20x_dev */
    TH02.begin();
    delay(100);

    /* Determine TH02_dev is available or not */
    ShowSerial.println("TH02_dev is available.\n");
}


void loop() {
    float temper = TH02.ReadTemperature();
    ShowSerial.print("Temperature: ");
    ShowSerial.print(temper);
    ShowSerial.println("C\r\n");
    //Serial.print("%\t");

    float humidity = TH02.ReadHumidity();
    ShowSerial.print("Humidity: ");
    ShowSerial.print(humidity);
    ShowSerial.println("%\r\n");
    delay(1000);
}
