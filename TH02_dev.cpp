#include "TH02_dev.h"
#include <Wire.h>
#include <Arduino.h>


void TH02_dev::begin(void) {
    /* Start IIC */
    //Wire.begin();
	TempHumi::begin(TH02_I2C_DEV_ID);
    /* TH02 don't need to software reset */
}

float TH02_dev::ReadTemperature(void) {
    /* Start a new temperature conversion */
    IIC_WriteReg(REG_CONFIG, CMD_MEASURE_TEMP);
    //delay(100);
    /* Wait until conversion is done */
    while (!isAvailable());
    uint16_t value = IIC_ReadData(REG_DATA_H,3);

    value = value >> 2;
    /*
        Formula:
        Temperature(C) = (Value/32) - 50
    */
    float temper = (value / 32.0) - 50.0;

    return temper;
}

float TH02_dev::ReadHumidity(void) {
    /* Start a new humility conversion */
    IIC_WriteReg(REG_CONFIG, CMD_MEASURE_HUMI);

    /* Wait until conversion is done */
    //delay(100);
    while (!isAvailable());
    uint16_t value = IIC_ReadData(REG_DATA_H,3);

    value = value >> 4;

    /*
        Formula:
        Humidity(%) = (Value/16) - 24
    */

    float humility = (value / 16.0) - 24.0;

    return humility;
}

/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t TH02_dev::isAvailable() {
    uint8_t status =  IIC_ReadReg(REG_STATUS);
    if (status & STATUS_RDY_MASK) {
        return 0;    //ready
    } else {
        return 1;    //not ready yet
    }
}


void TH02_dev::IIC_WriteCmd(uint8_t u8Cmd) {
 
	TempHumi::IIC_WriteCmd(u8Cmd);
}

uint8_t TH02_dev::IIC_ReadReg(uint8_t u8Reg) {
    /* Port to arduino */
    uint8_t Temp = 0;

    /* Send a register reading command */
    IIC_WriteCmd(u8Reg);

    Wire.requestFrom(TH02_I2C_DEV_ID, 1);
    while (Wire.available()) {
        Temp = Wire.read();
    }

    return Temp;
}

/*Write Reg*/
void TH02_dev::IIC_WriteReg(uint8_t u8Reg, uint8_t u8Data) {
    Wire.beginTransmission(TH02_I2C_DEV_ID);
    Wire.write(u8Reg); 
    Wire.write(u8Data);
    Wire.endTransmission();
}

uint16_t TH02_dev::IIC_ReadData(uint8_t u8Reg,uint8_t num) {
    /* Port to arduino */
    uint16_t Temp = IIC_ReadData2byte(u8Reg,num);
    return Temp;
}

uint16_t TH02_dev::IIC_ReadData2byte(uint8_t u8Reg,uint8_t num) {
    
     return TempHumi::IIC_ReadData2byte(u8Reg,num);
}

