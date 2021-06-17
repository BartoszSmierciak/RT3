/*
* @file encoder.h
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/
#include <modbus/modbus.h>
#include <stdint.h>
#include "encoderPrivate.h"
#include <stdbool.h>

uint32_t _encoderPositionH;
uint32_t _encoderPositionL;
uint32_t _encoderPosition;
uint32_t _encoderActualReverseState;
uint32_t _encoderTermResetState;
uint32_t _encoderSpeedH;
uint32_t _encoderSpeedL;
uint32_t _encoderSpeed;
uint32_t _encoderLimitSwitchState;
uint32_t _encoderPhysicalSTResolutionH;
uint32_t _encoderPhysicalSTResolutionL;
uint32_t _encoderPhysicalSTResolution;
uint32_t _encoderPhysicalMTResolutionH;
uint32_t _encoderPhysicalMTResolutionL;
uint32_t _encoderPhysicalMTResolution;
uint32_t _encoderScalingEnabled;
uint32_t _encoderSTResolutionH;
uint32_t _encoderSTResolutionL;
uint32_t _encoderSTResolution;
uint32_t _encoderTotResolutionH;
uint32_t _encoderTotResolutionL;
uint32_t _encoderTotResolution;
uint32_t _encoderPresetH;
uint32_t _encoderPresetL;
uint32_t _encoderPreset;
uint32_t _encoderOffsetH;
uint32_t _encoderOffsetL;
uint32_t _encoderOffset;
uint32_t _encoderCountDirection;
uint32_t _encoderSpeedMode;
uint32_t _encoderSpeedFilter;
uint32_t _encoderLimitSwitchEnable;
uint32_t _encoderLowLimitSwitchH;
uint32_t _encoderLowLimitSwitchL;
uint32_t _encoderLowLimitSwitch;
uint32_t _encoderHighLimitSwitchH;
uint32_t _encoderHighLimitSwitchL;
uint32_t _encoderHighLimitSwitch;
uint32_t _encoderDelay;
uint32_t _encoderErrorReg;
uint32_t _encoderDeviceResetStore;
uint32_t _encoderParameters;
uint32_t _encoderAutoStore;
uint32_t _encoderRestoreAllParameters;
uint32_t _encoderRestoreAplicationParameters;
uint32_t _encoderAutoTest;
uint32_t _encoderSoftwareVersion;
uint32_t _encoderSerialNumberH;
uint32_t _encoderSerialNumberL;
uint32_t _encoderSerialNumber;
uint32_t _encoderLifeCycleCounterH;
uint32_t _encoderLifeCycleCounterL;
uint32_t _encoderLifeCycleCounter;
uint32_t _encoderRollCounter;
uint32_t _encoderBaudrate;
uint32_t _encoderNumberData;
uint32_t _encoderParity;
uint32_t _encoderStopbits;
uint32_t _encoderCommUpdate;
uint32_t _encoderNodeAddress;
uint32_t _encoderNodeUpdate;
uint32_t _encoderAutoBaudEnable;
uint32_t _encoderAutoBaudTimeout;
uint32_t _encoderRestoreBusParameters;
uint32_t _encoderTermination;
uint32_t _encoderTermUpdate;



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

uint16_t EncoderReadModbus(int slaveAddress, int regAddress);

int EncoderWriteModbus(int slaveAddress, int regAddress, uint16_t value);

//Close modbus connection
void EncoderClose();

void EncoderPrintRegisters(int slaveAddress);

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
//Default is 1
uint32_t EncoderGetTermResetState(int slaveAddress);

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

uint32_t EncoderGetTotResolution(int slaveAddress);

void EncoderSetTotResolution(int slaveAddress, uint32_t totResolution);

uint32_t EncoderGetPreset(int slaveAddress);

void EncoderSetPreEncoderSet(int slaveAddress, uint32_t preEncoderSet);

uint32_t EncoderGetOffset(int slaveAddress);

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

uint32_t EncoderGetDeviceResetStore(int slaveAddress);

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

uint32_t EncoderGetBaudrate(int slaveAddress);

void EncoderSetBaudrate(int slaveAddress, uint32_t baudrate);

uint32_t EncoderGetNumberData(int slaveAddress);

void EncoderSetNumberData(int slaveAddress, uint32_t numberData);

uint32_t EncoderParity(int slaveAddress);

void EncoderSetParity(int slaveAddress, uint32_t parity);

uint32_t EncoderGetStopbits(int slaveAddress);

void EncoderSetStopbits(int slaveAddress, uint32_t stopbits);
        
uint32_t EncoderGetCommUpdate(int slaveAddress);

void EncoderSetCommUpdate(int slaveAddress, uint32_t commUpdate);

///MSB RW 8bit Node-ID 1...247 (1..0xF7)127
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
