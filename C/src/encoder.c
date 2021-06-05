/*
* @file encoder.c
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/

//"/dev/ttyS0", 9600, 'N', 8, 1
int EncoderInit(const char *device,
                int baud, char parity, int data_bit,
                int stop_bit)
{
    //Create a new RTU context with proper serial parameters (in this example,
    //device name /dev/ttyS0, baud rate 9600, no parity bit, 8 data bits, 1 stop bit)
    modbus_t *ctx = modbus_new_rtu(device, baud, parity, data_bit, stop_bit);
    if (!ctx) 
    {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(ctx) == -1) 
    {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
}
uint32_t EncoderReadModbus(int slaveAddress, int regAddress, int regToRead)
{
    //Set the Modbus address of the remote slave 
    modbus_set_slave(ctx, slaveAddress);

    uint32_t reg[regToRead];// will store read registers values
    
    int num = modbus_read_registers(ctx, regAddress, regToRead, reg);
    if (num != regToRead) 
    {// number of read registers is not the one expected
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }

    return reg;
}

int EncoderWriteModbus(int slaveAddress, int regAddress, uint32_t value)
{
    rc = modbus_write_register(ctx, regAddress, value);
    if (rc != 1) 
    {
        printf("ERROR modbus_write_register (%d)\n", rc);
        printf("Address = %d, value = %d (0x%X)\n", addr, value, value);        
    }
    return rc;
}

void EncoderClose()
{
    modbus_close(ctx);
    modbus_free(ctx);
}

/*!
* EncoderGet encoder position.
* \return position on success
*/
//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetPosition(int slaveAddress)
{
    _encoderPositionH = EncoderSendModbus(slaveAddress, encoderRegPositionH, 1);
    _encoderPositionL = EncoderSendModbus(slaveAddress, encoderRegPositionL, 1);
    _encoderPosition = _encoderPositionH | _encoderPositionL;
    return _position;
}

//8 bit MSB 0xF000
uint32_t EncoderGetActualReverseState(int slaveAddress)
{
    _encoderActualReverseState = EncoderSendModbus(slaveAddress, encoderRegActualReverseState, 1);
    return _encoderActualReverseState;
}
//8 bit MSB
uint32_t EncoderGetTermResetState()
{ 
    _encoderTermResetState = EncoderSendModbus(slaveAddress, encoderRegTermResetState, 1);
    return _encoderTermResetState;
} 
//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetSpeed()
{
    _encoderSpeedH = EncoderSendModbus(slaveAddress, encoderRegSpeedH, 1);
    _encoderSpeedL = EncoderSendModbus(slaveAddress, encoderRegSpeedL, 1);
    _encoderSpeed = _encoderSpeedH | _encoderSpeedL;
    return _encoderSpeed;
}
 
//8bit 0x000F
uint32_t EncoderGetLimitSwitchState()
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}
 
//2*32 bit MSB 0xFF00 LSB 0x00FF
uint32_t EncoderGetPhysicalSTResolution()
{
    _encoderPhysicalSTResolutionH = EncoderSendModbus(slaveAddress, encoderRegPhysicalSTResolutionH, 1);
    _encoderPhysicalSTResolutionL = EncoderSendModbus(slaveAddress, encoderRegPhysicalSTResolutionL, 1);
    _encoderPhysicalSTResolution = _encoderPhysicalSTResolutionH | _encoderPhysicalSTResolutionL;
    return _encoderPhysicalSTResolution;
}
    
uint32_t EncoderGetPhysicalMTResolution(int slaveAddress)
{
    _encoderPhysicalMTResolutionH = EncoderSendModbus(slaveAddress, encoderRegPhysicalMTResolutionH, 1);
    _encoderPhysicalMTResolutionL = EncoderSendModbus(slaveAddress, encoderRegPhysicalMTResolutionL, 1);
    _encoderPhysicalMTResolution = _encoderPhysicalMTResolutionH | _encoderPhysicalMTResolutionL;
    return _encoderPhysicalMTResolution;
}
    
/*!
* EncoderGet scaling enabled.
* 8 bit 0x000F
* \return TODO
*/
uint32_t EncoderGetScalingEnabled(int slaveAddress)
{
    _encoderScalingEnabled = EncoderSendModbus(slaveAddress, encoderScalingEnabled, 1);
    return _encoderScalingEnabled;
}
    
/*!
* Set scaling enabled.
* \param slaveAddress
* \param scalingEnabled
*/
void SetScalingEnabled(int slaveAddress, uint32_t scalingEnabled)
{
    _encoderScalingEnabled = scalingEnabled;
    EncoderWriteModbus(slaveAddress, regScalingEnabled, _encoderScalingEnabled)
}
    
uint32_t EncoderGetSTResolution(int slaveAddress)
{
    _encoderSTResolutionH = EncoderSendModbus(slaveAddress, encoderRegSTResolutionH, 1);
    _encoderSTResolutionL = EncoderSendModbus(slaveAddress, encoderRegSTResolutionL, 1);
    _encoderSTResolution = _encoderSTResolutionH | _encoderSTResolutionL;
    return _encoderSTResolution;
}

void SetSTResolution(int slaveAddress, uint32_t sTResolution)
{
    _encoderSTResolution = sTResolution;
    EncoderWriteModbus(slaveAddress, regSTResolution, _encoderSTResolution);
}
    
uint32_t EncoderGetTotResolution(int slaveAddress)
{
    _encoderTotResolutionH = EncoderSendModbus(slaveAddress, encoderRegTotResolutionH, 1);
    _encoderTotResolutionL = EncoderSendModbus(slaveAddress, encoderRegTotResolutionL, 1);
    _encoderTotResolution = _encoderTotResolutionH | _encoderTotResolutionL;
    return _encoderTotResolution;
}

void SetTotResolution(int slaveAddress, uint32_t totResolution)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encoderTotResolution);
}

uint32_t EncoderGetPreset(int slaveAddress)
{
    _encoderPresetH = EncoderSendModbus(slaveAddress, encoderRegPresetH, 1);
    _encoderPresetL = EncoderSendModbus(slaveAddress, encoderRegPresetL, 1);
    _encoderPreset = _encoderPresetH | _encoderPresetL;
    return _encoderPreset;
}
void SetPreset(int slaveAddress, uint32_t preset)
{
    _encoderPreset = preset;
    EncoderWriteModbus(slaveAddress, regPreset, _encoderPreset);
}
    
uint32_t EncoderGetOffset(int slaveAddress)
{
    _encoderOffsetH = EncoderSendModbus(slaveAddress, encoderRegOffsetH, 1);
    _encoderOffsetL = EncoderSendModbus(slaveAddress, encoderRegOffsetL, 1);
    _encoderOffset = _encoderOffsetH | _encoderOffsetL;
    return _encoderOffset;
}
    
uint32_t EncoderGetCountDirection(int slaveAddress)
{
    _encoderCountDirection = EncoderSendModbus(slaveAddress, encoderRegCountDirection, 1);
    return _encoderCountDirection;
}

void SetCountDirection(int slaveAddress, uint32_t countDirection)
{
    _encoderCountDirection = countDirection;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encoderCountDirection);
}
    
uint32_t EncoderGetSpeedMode(int slaveAddress)
{
    _encoderSpeedMode = EncoderSendModbus(slaveAddress, encoderRegSpeedMode, 1);
    return _encoderSpeedMode;
}

void SetSpeedMode(int slaveAddress, uint32_t speedMode)
{
    _encoderSpeedMode = SpeedMode;
    EncoderWriteModbus(slaveAddress, regSpeedMode, _encoderSpeedMode);
}
    
uint32_t EncoderGetSpeedFilter(int slaveAddress)
{
    _encoderSpeedFilter = EncoderSendModbus(slaveAddress, encoderRegSpeedFilter, 1);
    return _encoderSpeedFilter;
}

void SetSpeedFilter(int slaveAddress, uint32_t speedFilter)
{
    _encoderSpeedFilter = speedFilter;
    EncoderWriteModbus(slaveAddress, regSpeedFilter, _encoderSpeedFilter);
}
    
uint32_t EncoderGetLimitSwitchEnable(int slaveAddress)
{
    _encoderLimitSwitchEnable = EncoderSendModbus(slaveAddress, encoderRegLimitSwitchEnable, 1);
    return _encoderLimitSwitchEnable;
}

void SetLimitSwitchEnable(int slaveAddress, uint32_t limitSwitchEnable)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetLowLimitSwitch(int slaveAddress)
{
    _encoderLowLimitSwitchH = EncoderSendModbus(slaveAddress, encoderRegLowLimitSwitchH, 1);
    _encoderLowLimitSwitchL = EncoderSendModbus(slaveAddress, encoderRegLowLimitSwitchL, 1);
    _encoderLowLimitSwitch = _encoderLowLimitSwitchH | _encoderLowLimitSwitchL;
    return _encoderLowLimitSwitch;
}
}

void SetLowLimitSwitch(int slaveAddress, uint32_t lowLimitSwitch)
{
    _encoderLowLimitSwitch = lowLimitSwitch;
    EncoderWriteModbus(slaveAddress, regLowLimitSwitch, _encoderLowLimitSwitch);
}

uint32_t EncoderGetHighLimitSwitch(int slaveAddress)
{
    _encoderHighLimitSwitchH = EncoderSendModbus(slaveAddress, encoderRegHighLimitSwitchH, 1);
    _encoderHighLimitSwitchL = EncoderSendModbus(slaveAddress, encoderRegHighLimitSwitchL, 1);
    _encoderHighLimitSwitch = _encoderHighLimitSwitchH | _encoderHighLimitSwitchL;
    return _encoderHighLimitSwitch;
}

void SetHighLimitSwitch(int slaveAddress, uint32_t highLimitSwitch)
{
    _encoderHighLimitSwitch = highLimitSwitch;
    EncoderWriteModbus(slaveAddress, regHighLimitSwitch, _encoderHighLimitSwitch);
}
    
uint32_t EncoderGetDelay(int slaveAddress)
{
    _encoderDelay = EncoderSendModbus(slaveAddress, encoderRegDelay, 1);
    return _encoderDelay;
}

void SetDelay(int slaveAddress, uint32_t delay)
{
    _encoderDelay = delay;
    EncoderWriteModbus(slaveAddress, regDelay, _encoderDelay);
}
    
uint32_t EncoderGetErrorReg(int slaveAddress)
{
    _encoderErrorReg = EncoderSendModbus(slaveAddress, encoderRegErrorReg, 1);
    return _encoderErrorReg;
}

void SetErrorReg(int slaveAddress, uint32_t errorReg)
{
    _encoderErrorReg = errorReg;
    EncoderWriteModbus(slaveAddress, regErrorReg, _encoderErrorReg);
}
    
uint32_t EncoderGetDeviceResetStore(int slaveAddress)
{
    _encoderDeviceResetStore = EncoderSendModbus(slaveAddress, encoderRegDeviceResetStore, 1);
    return _encoderDeviceResetStore;
}

void SetDeviceResetStore(int slaveAddress, uint32_t deviceResetStore)
{
    _encoderDeviceResetStore = deviceResetStore;
    EncoderWriteModbus(slaveAddress, regDeviceResetStore, _encoderDeviceResetStore);
}
    
uint32_t EncoderGetParameters(int slaveAddress)
{
    _encoderParameters = EncoderSendModbus(slaveAddress, encoderRegParameters, 1);
    return _encoderParameters;
}

void SetParameters(int slaveAddress, uint32_t parameters)   
{
    _encoderParameters = parameters;
    EncoderWriteModbus(slaveAddress, regParameters, _encoderParameters);
}
    
uint32_t EncoderGetAutoStore(int slaveAddress)
{
    _encoderAutoStore = EncoderSendModbus(slaveAddress, encoderRegAutoStore, 1);
    return _encoderAutoStore;
}

void SetAutoStore(int slaveAddress, uint32_t autostore)
{
    _encoderAutoStore = autoStore;
    EncoderWriteModbus(slaveAddress, regAutoStore, _encoderAutoStore);
}
    
uint32_t EncoderGetRestoreAllParameters()
{
    _encoderRestoreAllParameters = EncoderSendModbus(slaveAddress, encoderRegRestoreAllParameters, 1);
    return _encoderRestoreAllParameters;
}

void SetRestoreAllParameters(int slaveAddress, uint32_t restoreAllParameters)
{
    _encoderRestoreAllParameters = restoreAllParameters;
    EncoderWriteModbus(slaveAddress, regRestoreAllParameters, _encoderRestoreAllParameters);
}
    
uint32_t EncoderGetRestoreAplicationParameters(int slaveAddress)
{
    _encoderRestoreAplicationParameters = EncoderSendModbus(slaveAddress, encoderRegRestoreAplicationParameters, 1);
    return _encoderRestoreAplicationParameters;
}

void SteRestoteAplicationParameters(int slaveAddress, uint32_t restoreAplicationParameters)
{
    _encoderRestoreAplicationParameters = restoreAplicationParameters;
    EncoderWriteModbus(slaveAddress, regRestoreAplicationParameters, _encoderRestoreAplicationParameters);
}
        
uint32_t EncoderGetAutoTest(int slaveAddress)
{
    _encoderAutoTest = EncoderSendModbus(slaveAddress, encoderRegAutoTest, 1);
    return _encoderAutoTest;
}

void SetAutoTest(int slaveAddress, uint32_t autoTest)
{
    _encoderAutoTest = autoTest;
    EncoderWriteModbus(slaveAddress, regAutoTest, _encoderAutoTest);
}
    
uint32_t EncoderGetSoftwareVersion(int slaveAddress)
{
    _encoderSoftwareVersion = EncoderSendModbus(slaveAddress, encoderRegSoftwareVersion, 1);
    return _encoderSoftwareVersion;
}
        
uint32_t EncoderGetSerialNumber(int slaveAddress)
{
    _encoderSerialNumberH = EncoderSendModbus(slaveAddress, encoderRegSerialNumberH, 1);
    _encoderSerialNumberL = EncoderSendModbus(slaveAddress, encoderRegSerialNumberL, 1);
    _encoderSerialNumber = _encoderSerialNumberH | _encoderSerialNumberL;
    return _encoderSerialNumber;
}
    
uint32_t EncoderGetLifeCycleCounter(int slaveAddress)
{
    _encoderLifeCycleCounterH = EncoderSendModbus(slaveAddress, encoderRegLifeCycleCounterH, 1);
    _encoderLifeCycleCounterL = EncoderSendModbus(slaveAddress, encoderRegLifeCycleCounterL, 1);
    _encoderLifeCycleCounter = _encoderLifeCycleCounterH | _encoderLifeCycleCounterL;
    return _encoderLifeCycleCounter;
}
    
uint32_t EncoderGetRollCounter(int slaveAddress)
{
    _encoderRollCounter = EncoderSendModbus(slaveAddress, encoderRegRollCounter, 1);
    return _encoderRollCounter;
}
        
uint32_t EncoderGetSerialParameters(int slaveAddress)
{
  //TODO: 4*8bits separate the variables
    _encoderSerialParameters = EncoderSendModbus(slaveAddress, encoderRegSerialParameters, 1);
    return _encoderSerialParameters;
}

void SetSerialParameters(int slaveAddress, uint32_t serialParameters)
{
    //TODO: 4*8bit separate the variables
    _encoderSerialParameters = totResolution;
    EncoderWriteModbus(slaveAddress, regSerialParameters, _encoderSerialParameters);
}
        
uint32_t EncoderGetCommUpdate(int slaveAddress)
{
    _encoderCommUpdate = EncoderSendModbus(slaveAddress, encoderRegCommUpdate, 1);
    return _encoderCommUpdate;
}

void SetCommUpdate(int slaveAddress, uint32_t commUpdate)
{
    _encoderCommUpdate = commUpdate;
    EncoderWriteModbus(slaveAddress, regCommUpdate, _encoderCommUpdate);
}
    
uint32_t EncoderGetNodeAddress(int slaveAddress)
{
    _encoderNodeAddress = EncoderSendModbus(slaveAddress, encoderRegNodeAddress, 1);
    return _encoderNodeAddress;
}

void SetNodeAddress(int slaveAddress, uint32_t nodeAddress)
{
    _encoderNodeAddress = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetNodeUpdate(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetNodeUpdate(int slaveAddress, uint32_t nodeUpdate)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetAutoBaudEnable(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetAutoBaudEnable(int slaveAddress, uint32_t autoBaudEnable)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetAutoBaudTimeout(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetAutoBaudTimeout(int slaveAddress, uint32_t autoBaudTimeout)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetRestoreBusParameters(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetRestoreBusParameters(int slaveAddress, uint32_t restoreBusParameters)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetTermination(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetTermination(int slaveAddress, uint32_t termination)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetTermUpdate(int slaveAddress)
{
    _encoderLimitSwitchState = EncoderSendModbus(slaveAddress, encoderRegSwitchState, 1);
    return _encoderLimitSwitchState;
}

void SetTermUpdate(int slaveAddress, uint32_t termUpdate)
{
    _encoderTotResolution = totResolution;
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
        
