/*
* @file encoder.h
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/
#include <modbus.h>
#include "encoderRegisters.h"

//Modbus contex
modbus_t *ctx;

/*!
* EncoderGet encoder position.
* \return position on success
*/
int EncoderInit(const char *device,
                int baud, char parity, int data_bit,
                int stop_bit);

uint16_t EncoderSendModbus(int slaveAddress, int regAddress, int regToRead);

int EncoderClose();

/*!
* EncoderGet encoder position.
* \return position on success
*/
//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetPosition(int slaveAddress);

//8 bit MSB 0xF000
uint32_t EncoderGetActualReverseState(int slaveAddress);

//8 bit MSB
uint32_t EncoderGetTermResetState();

//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetSpeed(int slaveAddress);

//8bit 0x000F
uint32_t EncoderGetLimitSwitchState(int slaveAddress);

//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetPhysicalSTResolution(int slaveAddress);

uint32_t EncoderGetPhysicalMTResolution(int slaveAddress);

/*!
* EncoderGet scaling enabled.
* 8 bit 0x000F
* \return TODO
*/
uint32_t EncoderGetScalingEnabled(int slaveAddress);

/*!
* Set scaling enabled.
* \param slaveAddress
* \param scalingEnabled
*/
void SetScalingEnabled(int slaveAddress, uint32_t scalingEnabled);

uint32_t EncoderGetSTResolution(int slaveAddress);

void SetSTResolution(int slaveAddress, uint32_t sTResolution);

uint32_t EncoderGetTotResolution(int slaveAddress);

void SetTotResolution(int slaveAddress, uint32_t totResolution);

uint32_t EncoderGetPreset(int slaveAddress);

void SetPreset(int slaveAddress, uint32_t preset);

uint32_t EncoderGetOffset(int slaveAddress);

uint32_t EncoderGetCountDirection(int slaveAddress);

void SetCountDirection(int slaveAddress, uint32_t countDirection);
    
uint32_t EncoderGetSpeedMode(int slaveAddress);

void SetSpeedMode(int slaveAddress, uint32_t speedMode);

uint32_t EncoderGetSpeedFilter(int slaveAddress);

void SetSpeedFilter(int slaveAddress, uint32_t speedFilter);

uint32_t EncoderGetLimitSwitchEnable(int slaveAddress);

void SetLimitSwitchEnable(int slaveAddress, uint32_t limitSwitchEnable);

uint32_t EncoderGetLowLimitSwitch(int slaveAddress);

void SetLowLimitSwitch(int slaveAddress, uint32_t lowLimitSwitch);

uint32_t EncoderGetHighLimitSwitch(int slaveAddress);

void SetHighLimitSwitch(int slaveAddress, uint32_t highLimitSwitch);

uint32_t EncoderGetDelay(int slaveAddress);

void SetDelay(int slaveAddress, uint32_t delay);

uint32_t EncoderGetErrorReg(int slaveAddress);

void SetErrorReg(int slaveAddress, uint32_t errorReg);

uint32_t EncoderGetDeviceResetStore(int slaveAddress);

void SetDeviceResetStore(int slaveAddress, uint32_t deviceResetStore);

uint32_t EncoderGetParameters(int slaveAddress);

void SetParameters(int slaveAddress, uint32_t parameters);
    
uint32_t EncoderGetAutoStore(int slaveAddress);

void SetAutoStore(int slaveAddress, uint32_t autostore);
 
uint32_t EncoderGetRestoreAllParameters(int slaveAddress);

void SetRestoreAllParameters(int slaveAddress, uint32_t restoreAllParameters);
    
uint32_t EncoderGetRestoreAplicationParameters(int slaveAddress);

void SteRestoteAplicationParameters(int slaveAddress, uint32_t restoreAplicationParameters);
        
uint32_t EncoderGetAutoTest(int slaveAddress);

void SetAutoTest(int slaveAddress, uint32_t autoTest);
    
uint32_t EncoderGetSoftwareVersion(int slaveAddress);
    
uint32_t EncoderGetSerialNumber(int slaveAddress);

uint32_t EncoderGetLifeCycleCounter(int slaveAddress);
 
uint32_t EncoderGetRollCounter(int slaveAddress);
   
uint32_t EncoderGetSerialParameters(int slaveAddress);

void SetSerialParameters(int slaveAddress, uint32_t serialParameters);
        
uint32_t EncoderGetCommUpdate(int slaveAddress);

void SetCommUpdate(int slaveAddress, uint32_t commUpdate);
    
uint32_t EncoderGetNodeAddress(int slaveAddress);

void SetNodeAddress(int slaveAddress, uint32_t nodeAddress);
  
uint32_t EncoderGetNodeUpdate(int slaveAddress);

void SetNodeUpdate(int slaveAddress, uint32_t nodeUpdate);
    
uint32_t EncoderGetAutoBaudEnable(int slaveAddress);

void SetAutoBaudEnable(int slaveAddress, uint32_t autoBaudEnable);
    
uint32_t EncoderGetAutoBaudTimeout(int slaveAddress);

void SetAutoBaudTimeout(int slaveAddress, uint32_t autoBaudTimeout);
    
uint32_t EncoderGetRestoreBusParameters(int slaveAddress);

void SetRestoreBusParameters(int slaveAddress, uint32_t restoreBusParameters);
  
uint32_t EncoderGetTermination(int slaveAddress);

void SetTermination(int slaveAddress, uint32_t termination);
    
uint32_t EncoderGetTermUpdate(int slaveAddress);

void SetTermUpdate(int slaveAddress, uint32_t termUpdate);
                                    

int _position;
        

        
