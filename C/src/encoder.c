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
    uint32_t positionH = EncoderSendModbus(slaveAddress, encoderRegPositionH, 1);
    uint32_t positionL = EncoderSendModbus(slaveAddress, encoderRegPositionL, 1);
    _position = positionH | positionL;
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
    EncoderWriteModbus(slaveAddress, regTotResolution, _encodertotResolution);
}
    
uint32_t EncoderGetPreset()
{
    
}
void SetPreset(int slaveAddress, uint32_t preset)
{
    
}
    
uint32_t EncoderGetOffset(int slaveAddress)
{
    
}
    
uint32_t EncoderGetCountDirection(int slaveAddress
{
    
}
void SetCountDirection(int slaveAddress, uint32_t countDirection)
{
    
}
    
uint32_t EncoderGetSpeedMode(int slaveAddress)
{
    
}
void SetSpeedMode(int slaveAddress, uint32_t speed)
{
    
}
    
uint32_t EncoderGetSpeedFilter(int slaveAddress)
{
    
}

void SetSpeedFilter(int slaveAddress, uint32_t speedLimit)
{
    
}
    
uint32_t EncoderGetLimitSwitchEnable(int slaveAddress)
{
    
}

void SetLimitSwitchEnable(int slaveAddress, uint32_t limitSwitchEnable)
{
    
}
    
uint32_t EncoderGetLowLimitSwitch(int slaveAddress)
{
    
}

void SetLowLimitSwitch(int slaveAddress, uint32_t lowLimitSwitch)
{
    
}

uint32_t EncoderGetHighLimitSwitch(int slaveAddress)
{
    
}

void SetHighLimitSwitch(int slaveAddress, uint32_t highLimitSwitch)
{
    
}
    
uint32_t EncoderGetDelay(int slaveAddress)
{
    
}

void SetDelay(int slaveAddress, uint32_t delay)
{
    
}
    
uint32_t EncoderGetErrorencoderReg(int slaveAddress)
{
    
}

void SetErrorencoderReg(int slaveAddress, uint32_t errorencoderReg)
{
    
}
    
uint32_t EncoderGetDeviceResetStore(int slaveAddress)
{
    
}

void SetDeviceResetStore(int slaveAddress, uint32_t deviceResetStore)
{
    
}
    
uint32_t EncoderGetParameters(int slaveAddress)
{
    
}

void SetParameters(int slaveAddress, uint32_t parameters)   
{
    
}
    
uint32_t EncoderGetAutoStore(int slaveAddress)
{
    
}

void SetAutoStore(int slaveAddress, uint32_t autostore)
{
    
}
    
uint32_t EncoderGetRestoreAllParameters()
{
    
}

void SetRestoreAllParameters(int slaveAddress, uint32_t restoreAllParameters)
{
    
}
    
uint32_t EncoderGetRestoreAplicationParameters(int slaveAddress)
{
    
}

void SteRestoteAplicationParameters(int slaveAddress, uint32_t restoreAplicationParameters)
{
    
}
        
uint32_t EncoderGetAutoTest(int slaveAddress)
{
    
}

void SetAutoTest(int slaveAddress, uint32_t autoTest)
{
    
}
    
uint32_t EncoderGetSoftwareVersion(int slaveAddress)
{
    
}
        
uint32_t EncoderGetSerialNumber(int slaveAddress)
{
    
}
    
uint32_t EncoderGetLifeCycleCounter(int slaveAddress)
{
    
}
    
uint32_t EncoderGetRollCounter(int slaveAddress)
{
    
}
        
uint32_t EncoderGetSerialParameters(int slaveAddress)
{
    
}

void SetSerialParameters(int slaveAddress, uint32_t serialParameters)
{
    
}
        
uint32_t EncoderGetCommUpdate(int slaveAddress)
{
    
}

void SetCommUpdate(int slaveAddress, uint32_t commUpdate)
{
    
}
    
uint32_t EncoderGetNodeAddress(int slaveAddress)
{
    
}

void SetNodeAddress(int slaveAddress, uint32_t nodeAddress)
{
    
}
    
uint32_t EncoderGetNodeUpdate(int slaveAddress)
{
    
}

void SetNodeUpdate(int slaveAddress, uint32_t nodeUpdate)
{
    
}
    
uint32_t EncoderGetAutoBaudEnable(int slaveAddress)
{
    
}

void SetAutoBaudEnable(int slaveAddress, uint32_t autoBaudEnable)
{
    
}
    
uint32_t EncoderGetAutoBaudTimeout(int slaveAddress)
{
    
}

void SetAutoBaudTimeout(int slaveAddress, uint32_t autoBaudTimeout)
{
    
}
    
uint32_t EncoderGetRestoreBusParameters(int slaveAddress)
{
    
}

void SetRestoreBusParameters(int slaveAddress, uint32_t restoreBusParameters)
{
    
}
    
uint32_t EncoderGetTermination(int slaveAddress)
{
    
}

void SetTermination(int slaveAddress, uint32_t termination)
{
    
}
    
uint32_t EncoderGetTermUpdate(int slaveAddress)
{
    
}

void SetTermUpdate(int slaveAddress, uint32_t termUpdate)
{
    
}
        
