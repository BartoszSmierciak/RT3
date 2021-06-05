/*
* @file encoder.h
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/
 #include <modbus.h>  

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
                                    

int _position;
        

        
