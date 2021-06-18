/*
* @file encoder.c
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/

#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>
#include "encoder.h"
#include "encoderRegisters.h"
#include <errno.h>
#include <unistd.h>

#include <sys/time.h>

modbus_t *ctx;

int EncoderInit(const char *device, int baud, char parity, int data_bit, int stop_bit)
{

    uint32_t tv_sec  = 0;          
    uint32_t tv_usec = 0;
    
    uint32_t resTimeSec = 0;
    uint32_t resTimeuSec = 40000;
    
    printf("\n");
    printf("Trying to connect...\n");
    ctx = modbus_new_rtu(device, baud, parity, data_bit, stop_bit);
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }
    if (NULL == ctx)
    {
        printf("Unable to create modbus context\n");
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }
    printf("Created modbus context\n");
    /* Get response timeout */
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Default response timeout: %d sec %d usec \n", tv_sec, tv_usec );

    /* Set response timeout */
    modbus_set_response_timeout(ctx, resTimeSec, resTimeuSec); 
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Set response timeout:     %d sec %d usec \n", tv_sec, tv_usec );
    return 0;
    
}

uint16_t EncoderReadModbus(int slaveAddress, int regAddress)
{
    //Set the Modbus address of the remote slave
    int rc = modbus_set_slave(ctx, slaveAddress);
    if (rc == -1) 
    {
        fprintf(stderr, "Invalid slave ID.\n");
        modbus_free(ctx);
        return -1;
    }
    
	// will store read register value
    uint16_t reg;

    int num = modbus_read_registers(ctx, regAddress, 1, &reg);
    if (num != 1)
    {
        fprintf(stderr, "Failed to read modbus. Num: %d\n", num);
    }
    return reg;
}

int EncoderWriteModbus(int slaveAddress, int regAddress, uint16_t value)
{

	modbus_set_slave(ctx, slaveAddress);
    int modbusAnswear = modbus_write_register(ctx, regAddress, value);
    if (modbusAnswear != 1)
   {
        printf("ERROR modbus_write_register (%d)\n", modbusAnswear);
        printf("Address = %d, value = %d (0x%X)\n", regAddress, value, value);
    }
    return modbusAnswear;
}

void EncoderClose()
{
    modbus_close(ctx);
    modbus_free(ctx);
}
void EncoderPrintRegisters(int slaveAddress)
{
	printf("Position: %u steps\n",EncoderGetPosition(slaveAddress));
	
	printf("Actual Reverse State: ");
	switch(EncoderGetActualReverseState(slaveAddress))
	{
		case 0: printf("CW\n"); break;
		case 1: printf("CCW\n"); break;
		default: printf("error\n");
	}

	printf("Term Reset State: ");
	switch(EncoderGetTermResetState(slaveAddress))
	{
		case 0: printf("off\n"); break;
		case 1: printf("on\n"); break;
		default: printf("error\n");
	}
	
	printf("Speed: %u\n", EncoderGetSpeed(slaveAddress));
	
	printf("Limit Switch State: %u\n", EncoderGetLimitSwitchState(slaveAddress));
	
	printf("Physical Single Turn Resolution: %u\n", EncoderGetPhysicalSTResolution(slaveAddress));
	
	printf("Physical Multi Turn Resolution: %u\n", EncoderGetPhysicalMTResolution(slaveAddress));
	
	printf("Scaling Enabled: ");
	switch(EncoderGetScalingEnabled(slaveAddress))
	{
		case 0: printf("off\n"); break;
		case 1: printf("on\n"); break;
		default: printf("error\n");
	}

	printf("Single Turn Resolution: %u\n", EncoderGetSTResolution(slaveAddress));
	
	printf("Total resolution: %u\n",EncoderGetTotResolution(slaveAddress));

	printf("Preset: %u\n", EncoderGetPreset(slaveAddress));
	
	printf("Offset: %u\n", EncoderGetOffset(slaveAddress));
	
	printf("Count direction: %u\n",EncoderGetCountDirection(slaveAddress));

    printf("Speed mode: ");
    switch(EncoderGetSpeedMode(slaveAddress))
    {
		case 0: printf("disable\n"); break;
		case 1: printf("rmp\n"); break;
		case 2: printf("degree/sec\n"); break;
		case 3: printf("steps/s\n"); break;
		case 4: printf("rad/sec\n"); break;
		case 5: printf("Hz\n"); break;
		default: printf("error\n");
	}
		
    printf("Speed filter. Moving average: %u\n",EncoderGetSpeedFilter(slaveAddress));
    
	printf("Limit Switch Enable: %u\n",EncoderGetLimitSwitchEnable(slaveAddress));
	
	printf("Low Limit Switch: %u\n",EncoderGetLowLimitSwitch(slaveAddress));
	
	printf("High Limit Switch: %u\n",EncoderGetHighLimitSwitch(slaveAddress));
	
	printf("Delay: %u\n",EncoderGetDelay(slaveAddress));
	
	printf("Error Register: %u\n",EncoderGetErrorReg(slaveAddress));
	
	printf("Device Reset Store: %u\n",EncoderGetDeviceResetStore(slaveAddress));
	
	printf("Parameters: %u\n",EncoderGetParameters(slaveAddress));
	
	printf("Auto Store: %u\n",EncoderGetAutoStore(slaveAddress));
	
	printf("Restore All Parameters: %u\n",EncoderGetRestoreAllParameters(slaveAddress));
	
	printf("Restore Application Parameters: %u\n",EncoderGetRestoreAplicationParameters(slaveAddress));
	
	printf("Auto Test: %u\n",EncoderGetAutoTest(slaveAddress));
	
	printf("Software Version: %u\n",EncoderGetSoftwareVersion(slaveAddress));
	
	printf("Serial Number: %u\n",EncoderGetSerialNumber(slaveAddress));
	
	printf("Life Cycle Counter %u\n",EncoderGetLifeCycleCounter(slaveAddress));
 
	printf("Roll Counter: %u\n",EncoderGetRollCounter(slaveAddress));
	
	printf("Baudrate: ");
	switch(EncoderGetBaudrate(slaveAddress))
	{
		case 0: printf("1200"); break;
		case 1: printf("2400"); break;
		case 2: printf("4800"); break;
		case 3: printf("9600"); break;
		case 4: printf("14400"); break;
		case 5: printf("19200"); break;
		case 6: printf("38400"); break;
		case 7: printf("56000"); break;
		case 8: printf("57600"); break;
		case 9: printf("115200"); break;
		case 10: printf("128000"); break;
		case 11: printf("256000"); break;
		default: printf("error read");
	}
	printf(" bps\n");
	
	printf("Number data bits: ");
	switch(EncoderGetNumberData(slaveAddress))
	{
		case 0: printf("6\n"); break;
		case 1: printf("7\n"); break;
		case 2: printf("8\n"); break;
		default: printf("error\n");
	}
	printf("Parity: ");
	switch(EncoderParity(slaveAddress))
	{
		case 0: printf("No\n"); break;
		case 1: printf("Odd\n"); break;
		case 2: printf("Even\n"); break;
		default: printf("error\n");
	}
	
	printf("Stop bits: %u\n",EncoderGetStopbits(slaveAddress));
    
	printf("Comm Update Execute: %u\n",EncoderGetCommUpdate(slaveAddress));

	printf("Node Address: %u\n",EncoderGetNodeAddress(slaveAddress));

	printf("Node Update: %u\n",EncoderGetNodeUpdate(slaveAddress));
    
	printf("Auto Baud Enable: %u\n",EncoderGetAutoBaudEnable(slaveAddress));
    
	printf("Auto Baud Timeout: %u\n",EncoderGetAutoBaudTimeout(slaveAddress));
    
	printf("Restore Bus Parameters: %u\n",EncoderGetRestoreBusParameters(slaveAddress));
  
	printf("Termination: %u\n",EncoderGetTermination(slaveAddress));
    
	printf("Term update: %u\n",EncoderGetTermUpdate(slaveAddress));
	
}
uint32_t EncoderGetPosition(int slaveAddress)
{
    _encoderPositionH = EncoderReadModbus(slaveAddress, encoderRegPositionH);
    _encoderPositionL = EncoderReadModbus(slaveAddress, encoderRegPositionL);
    _encoderPosition = (_encoderPositionH ) << 16 | _encoderPositionL;
    return _encoderPosition;
}

uint32_t EncoderGetActualReverseState(int slaveAddress)
{
    _encoderActualReverseState = EncoderReadModbus(slaveAddress, encoderRegActualReverseState);
    return _encoderActualReverseState;
}

uint32_t EncoderGetTermResetState(int slaveAddress)
{
    _encoderTermResetState = EncoderReadModbus(slaveAddress, encoderRegTermResetState);
    return _encoderTermResetState;
}

uint32_t EncoderGetSpeed(int slaveAddress)
{
    _encoderSpeedH = EncoderReadModbus(slaveAddress, encoderRegSpeedH);
    _encoderSpeedL = EncoderReadModbus(slaveAddress, encoderRegSpeedL);
    _encoderSpeed = (_encoderSpeedH) << 16 | _encoderSpeedL;
    return _encoderSpeed;
}

uint32_t EncoderGetLimitSwitchState(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderReadModbus(slaveAddress, encoderRegLimitSwitchState);
    return _encoderLimitSwitchState;
}

uint32_t EncoderGetPhysicalSTResolution(int slaveAddress)
{
    _encoderPhysicalSTResolutionH = EncoderReadModbus(slaveAddress, encoderRegPhysicalSTResolutionH);
    _encoderPhysicalSTResolutionL = EncoderReadModbus(slaveAddress, encoderRegPhysicalSTResolutionL);
    _encoderPhysicalSTResolution = (_encoderPhysicalSTResolutionH) << 16 | _encoderPhysicalSTResolutionL;
    return _encoderPhysicalSTResolution;
}

uint32_t EncoderGetPhysicalMTResolution(int slaveAddress)
{
    _encoderPhysicalMTResolutionH = EncoderReadModbus(slaveAddress, encoderRegPhysicalMTResolutionH);
    _encoderPhysicalMTResolutionL = EncoderReadModbus(slaveAddress, encoderRegPhysicalMTResolutionL);
    _encoderPhysicalMTResolution = (_encoderPhysicalMTResolutionH) << 16 | _encoderPhysicalMTResolutionL;
    return _encoderPhysicalMTResolution;
}

uint32_t EncoderGetScalingEnabled(int slaveAddress)
{
    _encoderScalingEnabled = EncoderReadModbus(slaveAddress, encoderRegScalingEnabled);
    return _encoderScalingEnabled;
}

void EncoderSetScalingEnabled(int slaveAddress, uint32_t scalingEnabled)
{
    _encoderScalingEnabled = scalingEnabled;
    EncoderWriteModbus(slaveAddress, encoderRegScalingEnabled, _encoderScalingEnabled);
}

uint32_t EncoderGetSTResolution(int slaveAddress)
{
    _encoderSTResolutionH = EncoderReadModbus(slaveAddress, encoderRegSTResolutionH);
    _encoderSTResolutionL = EncoderReadModbus(slaveAddress, encoderRegSTResolutionL);
    _encoderSTResolution = (_encoderSTResolutionH) << 16 | _encoderSTResolutionL;
    return _encoderSTResolution;
}

uint32_t EncoderGetTotResolution(int slaveAddress)
{
    _encoderTotResolutionH = EncoderReadModbus(slaveAddress, encoderRegTotResolutionH);
    _encoderTotResolutionL = EncoderReadModbus(slaveAddress, encoderRegTotResolutionL);
    _encoderTotResolution = (_encoderTotResolutionH) << 16 | _encoderTotResolutionL;
    return _encoderTotResolution;
}

void EncoderSetTotResolution(int slaveAddress, uint32_t totResolution)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, encoderRegTotResolutionL, _encoderTotResolution | 0x00FF);
    EncoderWriteModbus(slaveAddress, encoderRegTotResolutionH, (_encoderTotResolution | 0xFF00) >> 16);
}

uint32_t EncoderGetPreset(int slaveAddress)
{
    _encoderPresetH = EncoderReadModbus(slaveAddress, encoderRegPresetH);
    _encoderPresetL = EncoderReadModbus(slaveAddress, encoderRegPresetL);
    _encoderPreset = (_encoderPresetH) << 16 | _encoderPresetL;
    return _encoderPreset;
}

void EncoderSetPreset(int slaveAddress, uint32_t preset)
{
    _encoderPreset = preset;
    EncoderWriteModbus(slaveAddress, encoderRegPresetL, _encoderPreset | 0x00FF);
    EncoderWriteModbus(slaveAddress, encoderRegPresetH, (_encoderPreset | 0xFF00) >> 16);
    
}

uint32_t EncoderGetOffset(int slaveAddress)
{
    _encoderOffsetH = EncoderReadModbus(slaveAddress, encoderRegOffsetH);
    _encoderOffsetL = EncoderReadModbus(slaveAddress, encoderRegOffsetL);
    _encoderOffset = (_encoderOffsetH) << 16 | _encoderOffsetL;
    return _encoderOffset;
}

uint32_t EncoderGetCountDirection(int slaveAddress)
{
    _encoderCountDirection = EncoderReadModbus(slaveAddress, encoderRegCountDirection);
    return _encoderCountDirection;
}

void EncoderSetCountDirection(int slaveAddress, uint32_t countDirection)
{
    _encoderCountDirection = countDirection;
    EncoderWriteModbus(slaveAddress, encoderRegCountDirection, _encoderCountDirection);
}

uint32_t EncoderGetSpeedMode(int slaveAddress)
{
    _encoderSpeedMode = EncoderReadModbus(slaveAddress, encoderRegSpeedMode);
    return _encoderSpeedMode;
}

void EncoderSetSpeedMode(int slaveAddress, uint32_t speedMode)
{
    _encoderSpeedMode = speedMode;
    EncoderWriteModbus(slaveAddress, encoderRegSpeedMode, _encoderSpeedMode);
}

uint32_t EncoderGetSpeedFilter(int slaveAddress)
{
    _encoderSpeedFilter = EncoderReadModbus(slaveAddress, encoderRegSpeedFilter);
    return _encoderSpeedFilter;
}

void EncoderSetSpeedFilter(int slaveAddress, uint32_t speedFilter)
{
    _encoderSpeedFilter = speedFilter;
    EncoderWriteModbus(slaveAddress, encoderRegSpeedFilter, _encoderSpeedFilter);
}

uint32_t EncoderGetLimitSwitchEnable(int slaveAddress)
{
    _encoderLimitSwitchEnable = EncoderReadModbus(slaveAddress, encoderRegLimitSwitchEnable);
    return _encoderLimitSwitchEnable;
}

void EncoderSetLimitSwitchEnable(int slaveAddress, uint32_t limitSwitchEnable)
{
    _encoderLimitSwitchEnable = limitSwitchEnable;
    EncoderWriteModbus(slaveAddress, encoderRegLimitSwitchEnable, _encoderLimitSwitchEnable);
}

uint32_t EncoderGetLowLimitSwitch(int slaveAddress)
{
    _encoderLowLimitSwitchH = EncoderReadModbus(slaveAddress, encoderRegLowLimitSwitchH);
    _encoderLowLimitSwitchL = EncoderReadModbus(slaveAddress, encoderRegLowLimitSwitchL);
    _encoderLowLimitSwitch = (_encoderLowLimitSwitchH) << 16 | _encoderLowLimitSwitchL;
    return _encoderLowLimitSwitch;
}

void EncoderSetLowLimitSwitch(int slaveAddress, uint32_t lowLimitSwitch)
{
    _encoderLowLimitSwitch = lowLimitSwitch;
    EncoderWriteModbus(slaveAddress, encoderRegLowLimitSwitchL, _encoderLowLimitSwitch | 0x00FF);
    EncoderWriteModbus(slaveAddress, encoderRegLowLimitSwitchH, (_encoderLowLimitSwitch | 0xFF00) >> 16);
}

uint32_t EncoderGetHighLimitSwitch(int slaveAddress)
{
    _encoderHighLimitSwitchH = EncoderReadModbus(slaveAddress, encoderRegHighLimitSwitchH);
    _encoderHighLimitSwitchL = EncoderReadModbus(slaveAddress, encoderRegHighLimitSwitchL);
    _encoderHighLimitSwitch = (_encoderHighLimitSwitchH) << 16 | _encoderHighLimitSwitchL;
    return _encoderHighLimitSwitch;
}

void EncoderSetHighLimitSwitch(int slaveAddress, uint32_t highLimitSwitch)
{
    _encoderHighLimitSwitch = highLimitSwitch;
    EncoderWriteModbus(slaveAddress, encoderRegHighLimitSwitchL, _encoderHighLimitSwitch | 0x00FF);
    EncoderWriteModbus(slaveAddress, encoderRegHighLimitSwitchH, (_encoderHighLimitSwitch | 0x00FF ) >> 16);
}

uint32_t EncoderGetDelay(int slaveAddress)
{
    _encoderDelay = EncoderReadModbus(slaveAddress, encoderRegDelay);
    return _encoderDelay;
}

void EncoderSetDelay(int slaveAddress, uint32_t delay)
{
    _encoderDelay = delay;
    EncoderWriteModbus(slaveAddress, encoderRegDelay, _encoderDelay);
}

uint32_t EncoderGetErrorReg(int slaveAddress)
{
    _encoderErrorReg = EncoderReadModbus(slaveAddress, encoderRegErrorReg);
    return _encoderErrorReg;
}

void EncoderSetErrorReg(int slaveAddress, uint32_t errorReg)
{
    _encoderErrorReg = errorReg;
    EncoderWriteModbus(slaveAddress, encoderRegErrorReg, _encoderErrorReg);
}

uint32_t EncoderGetDeviceResetStore(int slaveAddress)
{
    _encoderDeviceResetStore = EncoderReadModbus(slaveAddress, encoderRegDeviceResetStore);
    return _encoderDeviceResetStore;
}

void EncoderSetDeviceResetStore(int slaveAddress, uint32_t deviceResetStore)
{
    _encoderDeviceResetStore = deviceResetStore;
    EncoderWriteModbus(slaveAddress, encoderRegDeviceResetStore, _encoderDeviceResetStore);
}

uint32_t EncoderGetParameters(int slaveAddress)
{
    _encoderParameters = EncoderReadModbus(slaveAddress, encoderRegParameters);
    return _encoderParameters;
}

void EncoderSetParameters(int slaveAddress, uint32_t parameters)
{
    _encoderParameters = parameters;
    EncoderWriteModbus(slaveAddress, encoderRegParameters, _encoderParameters);
}

uint32_t EncoderGetAutoStore(int slaveAddress)
{
    _encoderAutoStore = EncoderReadModbus(slaveAddress, encoderRegAutoStore);
    return _encoderAutoStore;
}

void EncoderSetAutoStore(int slaveAddress, uint32_t autoStore)
{
    _encoderAutoStore = autoStore;
    EncoderWriteModbus(slaveAddress, encoderRegAutoStore, _encoderAutoStore);
}

uint32_t EncoderGetRestoreAllParameters(int slaveAddress)
{
    _encoderRestoreAllParameters = EncoderReadModbus(slaveAddress, encoderRegRestoreAllParameters);
    return _encoderRestoreAllParameters;
}

void EncoderSetRestoreAllParameters(int slaveAddress, uint32_t restoreAllParameters)
{
    _encoderRestoreAllParameters = restoreAllParameters;
    EncoderWriteModbus(slaveAddress, encoderRegRestoreAllParameters, _encoderRestoreAllParameters);
}

uint32_t EncoderGetRestoreAplicationParameters(int slaveAddress)
{
    _encoderRestoreAplicationParameters = EncoderReadModbus(slaveAddress, encoderRegRestoreAplicationParameters);
    return _encoderRestoreAplicationParameters;
}

void SteRestoteAplicationParameters(int slaveAddress, uint32_t restoreAplicationParameters)
{
    _encoderRestoreAplicationParameters = restoreAplicationParameters;
    EncoderWriteModbus(slaveAddress, encoderRegRestoreAplicationParameters, _encoderRestoreAplicationParameters);
}

uint32_t EncoderGetAutoTest(int slaveAddress)
{
    _encoderAutoTest = EncoderReadModbus(slaveAddress, encoderRegAutoTest);
    return _encoderAutoTest;
}

void EncoderSetAutoTest(int slaveAddress, uint32_t autoTest)
{
    _encoderAutoTest = autoTest;
    EncoderWriteModbus(slaveAddress, encoderRegAutoTest, _encoderAutoTest);
}
    
uint32_t EncoderGetSoftwareVersion(int slaveAddress)
{
    _encoderSoftwareVersion = EncoderReadModbus(slaveAddress, encoderRegSoftwareVersion);
    return _encoderSoftwareVersion;
}
        
uint32_t EncoderGetSerialNumber(int slaveAddress)
{
    _encoderSerialNumberH = EncoderReadModbus(slaveAddress, encoderRegSerialNumberH);
    _encoderSerialNumberL = EncoderReadModbus(slaveAddress, encoderRegSerialNumberL);
    _encoderSerialNumber = (_encoderSerialNumberH) << 16 | _encoderSerialNumberL;
    return _encoderSerialNumber;
}
    
uint32_t EncoderGetLifeCycleCounter(int slaveAddress)
{
    _encoderLifeCycleCounterH = EncoderReadModbus(slaveAddress, encoderRegLifeCycleCounterH);
    _encoderLifeCycleCounterL = EncoderReadModbus(slaveAddress, encoderRegLifeCycleCounterL);
    _encoderLifeCycleCounter = (_encoderLifeCycleCounterH) << 16 | _encoderLifeCycleCounterL;
    return _encoderLifeCycleCounter;
}
    
uint32_t EncoderGetRollCounter(int slaveAddress)
{
    _encoderRollCounter = EncoderReadModbus(slaveAddress, encoderRegRollCounter);
    return _encoderRollCounter;
}
        
uint32_t EncoderGetBaudrate(int slaveAddress)
{
    _encoderBaudrate = EncoderReadModbus(slaveAddress, encoderRegBaudrate);
    return _encoderBaudrate;
}

void EncoderSetBaudrate(int slaveAddress, uint32_t baudrate)
{
    _encoderBaudrate = baudrate;
    EncoderWriteModbus(slaveAddress, encoderRegBaudrate, _encoderBaudrate);
}

uint32_t EncoderGetNumberData(int slaveAddress)
{
    _encoderNumberData = EncoderReadModbus(slaveAddress, encoderRegNumberData);
    return _encoderNumberData;
}

void EncoderSetNumberData(int slaveAddress, uint32_t numberData)
{
    _encoderNumberData = numberData;
    EncoderWriteModbus(slaveAddress, encoderRegNumberData, _encoderNumberData);
}

uint32_t EncoderParity(int slaveAddress)
{
    _encoderParity = EncoderReadModbus(slaveAddress, encoderRegParity);
    return _encoderParity;
}

void EncoderSetParity(int slaveAddress, uint32_t parity)
{
    _encoderParity = parity;
    EncoderWriteModbus(slaveAddress, encoderRegParity, _encoderParity);
}

uint32_t EncoderGetStopbits(int slaveAddress)
{
    _encoderStopbits = EncoderReadModbus(slaveAddress, encoderRegStopbits);
    return _encoderStopbits;
}

void EncoderSetStopbits(int slaveAddress, uint32_t stopbits)
{
    _encoderStopbits = stopbits;
    EncoderWriteModbus(slaveAddress, encoderRegStopbits, _encoderStopbits);
}

uint32_t EncoderGetCommUpdate(int slaveAddress)
{
    _encoderCommUpdate = EncoderReadModbus(slaveAddress, encoderRegCommUpdate);
    return _encoderCommUpdate;
}

void EncoderSetCommUpdate(int slaveAddress, uint32_t commUpdate)
{
    _encoderCommUpdate = commUpdate;
    EncoderWriteModbus(slaveAddress, encoderRegCommUpdate, _encoderCommUpdate);
}

uint32_t EncoderGetNodeAddress(int slaveAddress)
{
    _encoderNodeAddress = EncoderReadModbus(slaveAddress, encoderRegNodeAddress);
    return _encoderNodeAddress;
}

void EncoderSetNodeAddress(int slaveAddress, uint32_t nodeAddress)
{
    _encoderNodeAddress = nodeAddress;
    EncoderWriteModbus(slaveAddress, encoderRegNodeAddress, _encoderNodeAddress);
}

uint32_t EncoderGetNodeUpdate(int slaveAddress)
{
    _encoderNodeUpdate = EncoderReadModbus(slaveAddress, encoderRegNodeUpdate);
    return _encoderNodeUpdate;
}

void EncoderSetNodeUpdate(int slaveAddress, uint32_t nodeUpdate)
{
    _encoderNodeUpdate = nodeUpdate;
    EncoderWriteModbus(slaveAddress, encoderRegNodeUpdate, _encoderNodeUpdate);
}

uint32_t EncoderGetAutoBaudEnable(int slaveAddress)
{
    _encoderAutoBaudEnable = EncoderReadModbus(slaveAddress, encoderRegAutoBaudEnable);
    return _encoderAutoBaudEnable;
}

void EncoderSetAutoBaudEnable(int slaveAddress, uint32_t autoBaudEnable)
{
    _encoderAutoBaudEnable = autoBaudEnable;
    EncoderWriteModbus(slaveAddress, encoderRegAutoBaudEnable, _encoderAutoBaudEnable);
}

uint32_t EncoderGetAutoBaudTimeout(int slaveAddress)
{
    _encoderAutoBaudTimeout = EncoderReadModbus(slaveAddress, encoderRegAutoBaudTimeout);
    return _encoderAutoBaudTimeout;
}

void EncoderSetAutoBaudTimeout(int slaveAddress, uint32_t autoBaudTimeout)
{
    _encoderAutoBaudTimeout = autoBaudTimeout;
    EncoderWriteModbus(slaveAddress, encoderRegAutoBaudTimeout, _encoderAutoBaudTimeout);
}

uint32_t EncoderGetRestoreBusParameters(int slaveAddress)
{
    _encoderRestoreBusParameters = EncoderReadModbus(slaveAddress, encoderRegRestoreBusParameters);
    return _encoderRestoreBusParameters;
}

void EncoderSetRestoreBusParameters(int slaveAddress, uint32_t restoreBusParameters)
{
    _encoderRestoreBusParameters = restoreBusParameters;
    EncoderWriteModbus(slaveAddress, encoderRegRestoreBusParameters, _encoderRestoreBusParameters);
}

uint32_t EncoderGetTermination(int slaveAddress)
{
    _encoderTermination = EncoderReadModbus(slaveAddress, encoderRegTermination);
    return _encoderTermination;
}

void EncoderSetTermination(int slaveAddress, uint32_t termination)
{
    _encoderTermination = termination;
    EncoderWriteModbus(slaveAddress, encoderRegTermination, _encoderTermination);
}

uint32_t EncoderGetTermUpdate(int slaveAddress)
{
    _encoderTermUpdate = EncoderReadModbus(slaveAddress, encoderRegTermUpdate);
    return _encoderTermUpdate;
}

void EncoderSetTermUpdate(int slaveAddress, uint32_t termUpdate)
{
    _encoderTermUpdate = termUpdate;
    EncoderWriteModbus(slaveAddress, encoderRegTermUpdate, _encoderTermUpdate);
}
