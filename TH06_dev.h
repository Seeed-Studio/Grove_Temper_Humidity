
/*
    TH06_dev.h
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

#ifndef _TH06_DEV_H
#define _TH06_DEV_H

/****************************************************************************/
/***        Including Files                                               ***/
/****************************************************************************/

#include <Wire.h>
#include <Arduino.h>
#include "THsensor_base.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define TH06_I2C_DEV_ID               0x40
#define TH06_Humi_Hold_Master_Mode    0xE5
#define TH06_Humi_No_Hold_Master_Mode 0xF5
#define TH06_Temp_Hold_Master_Mode    0xE3
#define TH06_Temp_No_Hold_Master_Mode 0xF3
#define TH06_Reset                    0xFE
#define TH06_WR_RH                    0xE6
#define TH06_RD_RH                    0xE7
#define TH06_RTV_from_PRM             0xE0 

/****************************************************************************/
/***        Class Definition                                              ***/
/****************************************************************************/
class TH06_dev : public TempHumi {
	public:
	
		void begin();
		float ReadTemperature(void);
		float ReadHumidity(void);
		
		void IIC_WriteCmd(uint8_t u8Cmd);
		
		uint16_t IIC_ReadData2byte(uint8_t u8Reg,uint8_t num);
};


#endif 

