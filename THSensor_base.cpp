#include "THsensor_base.h"

#include <Arduino.h>
#include <Wire.h>


void TempHumi::begin(uint8_t u8Reg) {
    /* Start IIC */
	TempHumi::I2c_Dev_Id = u8Reg;
    Wire.begin();
    /* THSensor don't need to software reset */
}

float TempHumi::ReadTemperature(void) {
//TO BE DEFINED IN HARDWARE CHILD CLASS
}

float TempHumi::ReadHumidity(void) {
//TO BE DEFINED IN HARDWARE CHILD CLASS  
}

/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t TempHumi::isAvailable() {
    //TO BE DEFINED IN HARDWARE CHILD CLASS
}


void TempHumi::IIC_WriteCmd(uint8_t u8Cmd) {
   /* Port to arduino */
    Wire.beginTransmission(TempHumi::I2c_Dev_Id);
    Wire.write(u8Cmd);
    Wire.endTransmission();
}

/*num=1*/
uint8_t TempHumi::IIC_ReadReg(uint8_t u8Reg,uint8_t num) {
    //TO BE DEFINED IN HARDWARE CHILD CLASS
}


/*Write Reg*/
void TempHumi::IIC_WriteReg(uint8_t u8Reg, uint8_t u8Data) {
	//TO BE DEFINED IN HARDWARE CHILD CLASSe.endTransmission();
}

uint16_t IIC_ReadData(void){
	//TO BE DEFINED IN HARDWARE CHILD CLASS
}

/**get data**/
uint16_t TempHumi::IIC_ReadData2byte(uint8_t u8Reg,uint8_t num){
	uint16_t TempData = 0;
    uint16_t tmpArray[num] = {0};

    int cnt = 0;
    
    IIC_WriteCmd(u8Reg);
    
    Wire.requestFrom(TempHumi::I2c_Dev_Id, num);
    while (Wire.available()) 
    {
        tmpArray[cnt] = Wire.read();
        cnt++;
    }
 
    TempData = (tmpArray[num-2] << 8) | (tmpArray[num-1]);
    return TempData;
	
	
	
}
