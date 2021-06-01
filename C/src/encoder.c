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
uint16_t EncoderSendModbus(int slaveAddress, int regAddress, int regToRead)
{
    //Set the Modbus address of the remote slave (to 3)
    modbus_set_slave(ctx, slaveAddress);


    uint16_t reg[regToRead];// will store read registers values

    //Read 5 holding registers starting from address 10
    int num = modbus_read_registers(ctx, regAddress, regToRead, reg);
    if (num != regToRead) 
    {// number of read registers is not the one expected
        fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    }

    return reg;
}



int EncoderClose()
{
    modbus_close(ctx);
    modbus_free(ctx);
}
/*!
* EncoderGet encoder position.
* \return position on success
*/
int EncoderGetPosition();
        
int EncoderGetActualReverseState();
    
int EncoderGetTermResetState();
    
int EncoderGetSpeed();
    
int EncoderGetLimitSwitchState();
    
int EncoderGetPhysicalSTResolution();
    
int EncoderGetPhysicalMTResolution();
    
/*!
* EncoderGet scaling enabled.
* \return TODO
*/
int EncoderGetScalingEnabled();
    
/*!
* Set scaling enabled.
* \param scalingEnabled
*/
void SetScalingEnabled(int scalingEnabled);
    
int EncoderGetSTResolution();
void SetSTResolution(int stResolution);
    
int EncoderGetTotResolution();
void SetTotResolution(int totResolution);
    
int EncoderGetPreset();
void SetPreset(int preset);
    
int EncoderGetOffset();
    
int EncoderGetCountDirection();
void SetCountDirection(int countDirection);
    
int EncoderGetSpeedMode();
void SetSpeedMode(int speed);
    
int EncoderGetSpeedFilter();
void SetSpeedFilter(int speedLimit);
    
int EncoderGetLimitSwitchEnable();
void SetLimitSwitchEnable(int limitSwitchEnable);
    
int EncoderGetLowLimitSwitch();
void SetLowLimitSwitch(int lowLimitSwitch);
    
int EncoderGetHighLimitSwitch();
void SetHighLimitSwitch(int highLimitSwitch);
    
int EncoderGetDelay();
void SetDelay(int delay);
    
int EncoderGetErrorencoderReg();
void SetErrorencoderReg(int errorencoderReg);
    
int EncoderGetDeviceResetStore();
void SetDeviceResetStore(int deviceResetStore);
    
int EncoderGetParameters();
void SetParameters(int parameters);
    
int EncoderGetAutoStore();
void SetAutoStore(int autostore);
    
int EncoderGetRestoreAllParameters();
void SetRestoreAllParameters(int restoreAllParameters);
    
int EncoderGetRestoreAplicationParameters();
void SteRestoteAplicationParameters(int restoreAplicationparameters);
        
int EncoderGetAutoTest();
void SetAutoTest(int autoTest);
    
int EncoderGetSoftwareVersion();
        
int EncoderGetSerialNumber();
    
int EncoderGetLifeCycleCounter();
    
int EncoderGetRollCounter();
        
int EncoderGetSerialParameters();
void SetSerialParameters(int serialParameters);
        
int EncoderGetCommUpdate();
void SetCommUpdate(int commUpdate);
    
int EncoderGetNodeAddress();
void SetNodeAddress(int nodeAddress);
    
int EncoderGetNodeUpdate();
void SetNodeUpdate(int nodeUpdate);
    
int EncoderGetAutoBaudEnable();
void SetAutoBaudEnable(int autoBaudEnable);
    
int EncoderGetAutoBaudTimeout();
void SetAutoBaudTimeout(int autoBaudTimeout);
    
int EncoderGetRestoreBusParameters();
void SetRestoreBusParameters(int restoreBusParameters);
    
int EncoderGetTermination();
void SetTermination(int termination);
    
int EncoderGetTermUpdate();
void SetTermUpdate(int termUpdate);
        
