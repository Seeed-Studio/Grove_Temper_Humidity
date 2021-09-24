/*
    Demo name   : TH06_dev demo
    Usage       : DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
    Author      : Oliver Wang from Seeed Studio
    Version     : V0.1
*/

#include "TH06_dev.h"
#include "Arduino.h"
#include "Wire.h"

TH06_dev TH06;

void setup() {
    Serial.begin(9600);        // start serial for output

    Serial.println("****TH06_dev demo by seeed studio****\n");
    /* Reset HP20x_dev */
    TH06.begin();

}

void loop() {
   float temper = TH06.ReadTemperature();
    Serial.print("Temperature: ");
    Serial.print(temper);
    Serial.println("C\r\n");
    //Serial.print("%\t");

    float humidity = TH06.ReadHumidity();
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%\r\n");
    delay(1000);
}
