/*
    Demo name   : TH06_dev demo
    Usage       : DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
    Author      : Oliver Wang from Seeed Studio
    Version     : V0.1
*/

#include "TH06_dev.h"
#include "Arduino.h"
#include "Wire.h"

void setup() {
    Serial.begin(9600);        // start serial for output

    Serial.println("****TH06_dev demo by seeed studio****\n");
    /* Power up,delay 150ms,until voltage is stable */
    delay(150);
    /* Reset HP20x_dev */
    TH06.begin();
    delay(100);

    /* Determine TH02_dev is available or not */
    Serial.println("TH06_dev is available.\n");

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
