#ifndef _THSENEOR_BASE_H
#define _THSENEOR_BASE_H

#include <Arduino.h>
#include "THSensor_base.h"

class TempHumi{
public:
    void begin(uint8_t u8Reg);
    void IIC_WriteCmd(uint8_t u8Cmd);
    uint16_t IIC_ReadData2byte(uint8_t u8Reg,uint8_t num);

    
    uint8_t isAvailable();
    float ReadTemperature(void);
    float ReadHumidity(void);
    uint16_t IIC_ReadData(void);
    uint8_t IIC_ReadReg(uint8_t u8Reg,uint8_t num);
    void IIC_WriteReg(uint8_t u8Reg, uint8_t u8Data);

private:
	uint8_t I2c_Dev_Id;

};



#endif 

