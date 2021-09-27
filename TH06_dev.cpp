
#include "TH06_dev.h"
#include <Arduino.h>
#include <Wire.h>



void TH06_dev::begin(void) {
	/* Start IIC */
    //Wire.begin();
	TempHumi::begin(TH06_I2C_DEV_ID);
    /* TH06 don't need to software reset */
}

/* Read TH06's Temperature */
float TH06_dev::ReadTemperature(void)
{
 /*  */
 float Temp_Code = IIC_ReadData2byte(TH06_Temp_Hold_Master_Mode,2);
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
  float  RH_Code = IIC_ReadData2byte(TH06_Humi_Hold_Master_Mode,2);
  
  /*
		Formula:
        Humidity(%) = (125*RH_Code)/65536 - 6
 */
  float value = (125*RH_Code)/65536;
  float value1 = value - 6;
  return value1;
}


void TH06_dev::IIC_WriteCmd(uint8_t u8Cmd)
{
	TempHumi::IIC_WriteCmd(u8Cmd);
}

uint16_t TH06_dev::IIC_ReadData2byte(uint8_t u8Reg,uint8_t num)
{
    return TempHumi::IIC_ReadData2byte(u8Reg,num);
}

