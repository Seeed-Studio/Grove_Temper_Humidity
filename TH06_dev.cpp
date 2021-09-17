/*
    TH06_dev.cpp
    Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR

    Copyright (c) 2014 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Oliver Wang
    Create Time: April 2014
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/


/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "TH06_dev.h"
#include <arduino.h>
#include <Wire.h>
/* Use Serial IIC */
#ifdef SERIAL_IIC
#endif

TH06_dev TH06;
/****************************************************************************/
/***       Local Variable                                                 ***/
/****************************************************************************/


/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

void TH06_dev::begin(void) {
	/* Start IIC */
    Wire.begin();
    /* TH02 don't need to software reset */
}

/* Read TH06's Temperature */
float TH06_dev::ReadTemperature(void)
{
 /*  */
 float Temp_Code = TH06_IIC_ReadData2byte(TH06_Temp_Hold_Master_Mode);

 /*
		Formula:
        Temperature(C) = (175.2*Temp_Code)/65536 - 46.85
 
 */
 float value = (175.72*Temp_Code)/65536;
 float  value1 = value - 46.85;
  return value1;
}

/* Read TH06's Humidity*/
float TH06_dev::ReadHumidity(void)
{
  float  RH_Code = TH06_IIC_ReadData2byte(TH06_Humi_Hold_Master_Mode);
  
  /*
		Formula:
        Humidity(%) = (125*RH_Code)/65536 - 6
 */
  float value = (125*RH_Code)/65536;
  float value1 = value - 6;
  return value1;
}


void TH06_dev::TH06_IIC_WriteCmd(uint8_t u8Cmd)
{
	/* Port to arduino */
    Wire.beginTransmission(TH06_I2C_DEV_ID);
    Wire.write(u8Cmd);
    int error = Wire.endTransmission();
	
	/* if return error print error's value */
    if (error !=0)
    {
      Serial.print("error's value: ");
      Serial.println(error);
    }
}

uint16_t TH06_dev::TH06_IIC_ReadData2byte(uint8_t u8Reg)
{
    uint16_t TempData = 0;
    uint16_t tmpArray[2] = {0};

    int cnt = 0;
    
    TH06_IIC_WriteCmd(u8Reg);
    
    Wire.requestFrom(TH06_I2C_DEV_ID, 2);
    while (Wire.available()) 
    {
        tmpArray[cnt] = Wire.read();
        cnt++;
    }
 
    TempData = (tmpArray[0] << 8) | (tmpArray[1]);
    return TempData;

}
