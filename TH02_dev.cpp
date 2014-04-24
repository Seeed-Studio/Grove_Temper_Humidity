/*
 * File name  : TH02_dev.cpp
 * Description: Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
 * Author     : Oliver Wang from Seeed studio
 * Version    : V0.1
 * Create Time: 2014/04
 * Change Log :
*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "TH02_dev.h"
#include <Wire.h>
#include <Arduino.h>
/* Use Serial IIC */
#ifdef SERIAL_IIC
#endif


TH02_dev TH02;
/****************************************************************************/
/***       Local Variable                                                 ***/
/****************************************************************************/


/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/
/*
 **@ Function name: TH02_dev
 **@ Description: Constructor
 **@ Input: none
 **@ OutPut: none
 **@ Retval: none
*/
TH02_dev::TH02_dev()
{

}

/*
 **@ Function name: begin
 **@ Description: Initialize TH02_dev
 **@ Input: none
 **@ OutPut: none
 **@ Retval: none
*/
void TH02_dev::begin(void)
{
    /* Start IIC */
    Wire.begin();
	/* TH02 don't need to software reset */
}

float TH02_dev::ReadTemperature(void)
{    
    /* Start a new temperature conversion */
	TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_TEMP);	 	 
    //delay(100);
	/* Wait until conversion is done */
	while(!isAvailable());
	uint16_t value = TH02_IIC_ReadData();
	
	value = value >> 2;
	/* 
	  Formula:
      Temperature(C) = (Value/32) - 50	  
	*/	
	float temper = (value/32.0)-50.0;
	
	return temper;
}
 
float TH02_dev::ReadHumidity(void)
{
 /* Start a new humility conversion */
	TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_HUMI);
	
	/* Wait until conversion is done */
	//delay(100);
	while(!isAvailable());
	uint16_t value = TH02_IIC_ReadData();
	
	value = value >> 4;
 
	/* 
	  Formula:
      Humidity(%) = (Value/16) - 24	  
	*/	

	float humility = (value/16.0)-24.0;
	
	return humility;
}
/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t TH02_dev::isAvailable()
{
    uint8_t status =  TH02_IIC_ReadReg(REG_STATUS);
	if(status & STATUS_RDY_MASK)
	{
	    return 0;    //ready
	}
	else
	{
	    return 1;    //not ready yet
	}
}

/*
 **@ Function name: TH02_IIC_WriteCmd
 **@ Description:
 **@ Input:
 **@ OutPut:
 **@ Retval:
*/
void TH02_dev::TH02_IIC_WriteCmd(uint8_t u8Cmd)
{		
	/* Port to arduino */
	Wire.beginTransmission(TH02_I2C_DEV_ID);
	Wire.write(u8Cmd);
	Wire.endTransmission();
}

/*
 **@ Function name: TH02_IIC_ReadReg
 **@ Description:
 **@ Input:
 **@ OutPut:
 **@ Retval:  
*/
uint8_t TH02_dev::TH02_IIC_ReadReg(uint8_t u8Reg)
{
    /* Port to arduino */
    uint8_t Temp = 0;
	
	/* Send a register reading command */
    TH02_IIC_WriteCmd(u8Reg);	
		 
	Wire.requestFrom(TH02_I2C_DEV_ID, 1);	 
	while(Wire.available())
	{
	    Temp = Wire.read();	 
	}
		
	return Temp;
} 
/*
 **@ Function name: TH02_IIC_WriteReg
 **@ Description:
 **@ Input:
 **@ OutPut:
 **@ Retval:
*/
void TH02_dev::TH02_IIC_WriteReg(uint8_t u8Reg,uint8_t u8Data)
{           
	Wire.beginTransmission(TH02_I2C_DEV_ID);	 
	Wire.write(u8Reg);	 
	Wire.write(u8Data);	 
	Wire.endTransmission();	 
}


/*
 **@ Function name: TH02_IIC_ReadData
 **@ Description:
 **@ Input:
 **@ OutPut:
 **@ Retval:
*/
uint16_t TH02_dev::TH02_IIC_ReadData(void)
{                        
	/* Port to arduino */	 
	uint16_t Temp = TH02_IIC_ReadData2byte(); 
	return Temp;
}

/*
 **@ Function name: TH02_IIC_ReadData2byte
 **@ Description:
 **@ Input:
 **@ OutPut:
 **@ Retval:
*/
// uint16_t TH02_dev::TH02_IIC_ReadData2byte(void)
// {	
	// uint16_t TempData = 0;
	// uint16_t tmpArray[2]={0};
	 	
	// tmpArray[0] = (uint16_t)TH02_IIC_ReadReg(REG_DATA_H);	 
	// tmpArray[1] = (uint16_t)TH02_IIC_ReadReg(REG_DATA_L);
 
	// /* MSB */
	// TempData = tmpArray[0]<<8 | tmpArray[1]; 
	// return TempData;
// } 
uint16_t TH02_dev::TH02_IIC_ReadData2byte()
{
    uint16_t TempData = 0;
	uint16_t tmpArray[3]={0};

	int cnt = 0;
	TH02_IIC_WriteCmd(REG_DATA_H);	
	
	Wire.requestFrom(TH02_I2C_DEV_ID, 3);	 
	while(Wire.available())
	{
	    tmpArray[cnt] = (uint16_t)Wire.read();        	        	
		cnt++;
	}
	/* MSB */
	TempData = (tmpArray[1]<<8)|(tmpArray[2]); 
	return TempData;
}