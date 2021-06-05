/*
* @file encoder.h
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/
#include <modbus.h>
#include "encoderRegisters.h"
#include "encoderPrivate.h"

//Modbus contex
modbus_t *ctx;

/*!
* Initialisation of encoder. Set parameters of connections and connect to encoder
* \param device
* \param baud
* \param parity
* \param data_bit
* \param stop_bit
* \return 0 on success
*/
int EncoderInit(const char *device, int baud, char parity, int data_bit, int stop_bit);

uint32_t EncoderReadModbus(int slaveAddress, int regAddress, int regToRead);

int EncoderWriteModbus(int slaveAddress, int regAddress, uint32_t value);

//Close modbus connection
int EncoderClose();

/*!
* Get encoder position.
* Read two 32 bit high (MSB 0xFF00) and low (LSB 0x00FF) 
* registers of position and return sum of them.
* \param slaveAddress The node adress of the encoder
* \return position on success
*/
uint32_t EncoderGetPosition(int slaveAddress);

/*!
* Get encoder reverse state.
* Read 8 bit (MSB 0xF000) register of reverse state.
* Actual State CW = 0, CCW = 1
* Default is 0
* \param slaveAddress The node adress of the encoder
* \return Reverse state on success
*/
uint32_t EncoderGetActualReverseState(int slaveAddress);

//8 bit MSB 0xF000
//Termination on = 1, off = 0
//Default is 1g
uint32_t EncoderGetTermRestState();

//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetSpeed(int slaveAddress);

//8bit 0x000F
//default 0
uint32_t EncoderGetLimitSwitchState(int slaveAddress);

//2*32 bit MSB 0xFF00 LSB 0x00FF
//defalt
//H 0
//L 8192
uint32_t EncoderGetPhysicalSTResolution(int slaveAddress);

//2*32 bit MSB 0xFF00 LSB 0x00FF 
//defalt
//H 0
//L 4096
uint32_t EncoderGetPhysicalMTResolution(int slaveAddress);

/*!
* Get scaling enabled.
* 8 bit 0x000F
* \return TODO
*/
uint32_t EncoderGetScalingEnabled(int slaveAddress);

/*!
* Set scaling enabled.
* \param slaveAddress
* \param scalingEnabled
*/
void EncoderSetScalingEnabled(int slaveAddress, uint32_t scalingEnabled);

uint32_t EncoderGetSTResolution(int slaveAddress);

void EncoderSetSTResolution(int slaveAddress, uint32_t sTResolution);

uint32_t EncoderGetTotResolution(int slaveAddress);

void EncoderSetTotResolution(int slaveAddress, uint32_t totResolution);

uint32_t EncoderGetPreEncoderSet(int slaveAddress);

void EncoderSetPreEncoderSet(int slaveAddress, uint32_t preEncoderSet);

uint32_t EncoderGetOffEncoderSet(int slaveAddress);

uint32_t EncoderGetCountDirection(int slaveAddress);

void EncoderSetCountDirection(int slaveAddress, uint32_t countDirection);
    
uint32_t EncoderGetSpeedMode(int slaveAddress);

void EncoderSetSpeedMode(int slaveAddress, uint32_t speedMode);

uint32_t EncoderGetSpeedFilter(int slaveAddress);

void EncoderSetSpeedFilter(int slaveAddress, uint32_t speedFilter);

uint32_t EncoderGetLimitSwitchEnable(int slaveAddress);

void EncoderSetLimitSwitchEnable(int slaveAddress, uint32_t limitSwitchEnable);

uint32_t EncoderGetLowLimitSwitch(int slaveAddress);

void EncoderSetLowLimitSwitch(int slaveAddress, uint32_t lowLimitSwitch);

uint32_t EncoderGetHighLimitSwitch(int slaveAddress);

void EncoderSetHighLimitSwitch(int slaveAddress, uint32_t highLimitSwitch);

uint32_t EncoderGetDelay(int slaveAddress);

void EncoderSetDelay(int slaveAddress, uint32_t delay);

uint32_t EncoderGetErrorReg(int slaveAddress);

void EncoderSetErrorReg(int slaveAddress, uint32_t errorReg);

uint32_t EncoderGetDeviceReEncoderSetStore(int slaveAddress);

void EncoderSetDeviceReEncoderSetStore(int slaveAddress, uint32_t deviceReEncoderSetStore);

uint32_t EncoderGetParameters(int slaveAddress);

void EncoderSetParameters(int slaveAddress, uint32_t parameters);
    
uint32_t EncoderGetAutoStore(int slaveAddress);

void EncoderSetAutoStore(int slaveAddress, uint32_t autostore);
 
uint32_t EncoderGetRestoreAllParameters(int slaveAddress);

void EncoderSetRestoreAllParameters(int slaveAddress, uint32_t restoreAllParameters);
    
uint32_t EncoderGetRestoreAplicationParameters(int slaveAddress);

void SteRestoteAplicationParameters(int slaveAddress, uint32_t restoreAplicationParameters);
        
uint32_t EncoderGetAutoTest(int slaveAddress);

void EncoderSetAutoTest(int slaveAddress, uint32_t autoTest);
    
uint32_t EncoderGetSoftwareVersion(int slaveAddress);
    
uint32_t EncoderGetSerialNumber(int slaveAddress);

uint32_t EncoderGetLifeCycleCounter(int slaveAddress);
 
uint32_t EncoderGetRollCounter(int slaveAddress);
   
uint32_t EncoderGetSerialParameters(int slaveAddress);

void EncoderSetSerialParameters(int slaveAddress, uint32_t serialParameters);
        
uint32_t EncoderGetCommUpdate(int slaveAddress);

void EncoderSetCommUpdate(int slaveAddress, uint32_t commUpdate);
    
uint32_t EncoderGetNodeAddress(int slaveAddress);

void EncoderSetNodeAddress(int slaveAddress, uint32_t nodeAddress);
  
uint32_t EncoderGetNodeUpdate(int slaveAddress);

void EncoderSetNodeUpdate(int slaveAddress, uint32_t nodeUpdate);
    
uint32_t EncoderGetAutoBaudEnable(int slaveAddress);

void EncoderSetAutoBaudEnable(int slaveAddress, uint32_t autoBaudEnable);
    
uint32_t EncoderGetAutoBaudTimeout(int slaveAddress);

void EncoderSetAutoBaudTimeout(int slaveAddress, uint32_t autoBaudTimeout);
    
uint32_t EncoderGetRestoreBusParameters(int slaveAddress);

void EncoderSetRestoreBusParameters(int slaveAddress, uint32_t restoreBusParameters);
  
uint32_t EncoderGetTermination(int slaveAddress);

void EncoderSetTermination(int slaveAddress, uint32_t termination);
    
uint32_t EncoderGetTermUpdate(int slaveAddress);

void EncoderSetTermUpdate(int slaveAddress, uint32_t termUpdate);
