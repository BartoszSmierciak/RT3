/*
* @file encoder.h
* @author Bartosz Śmierciak
* @Date 2021-05-31
*
* @brief A brief description of encoder.h.
*/
 #include <modbus.h>   
/*!
* EncoderGet encoder position.
* \return position on success
*/
int EncoderInit();

int EncoderSendModbus();

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
        
static const uint16_t encoderRegPositionH                      = 0x9C42;
static const uint16_t encoderRegPositionL                      = 0x9C43;
static const uint16_t encoderRegActualReverseState             = 0x9C44;
static const uint16_t encoderRegTermResetState                 = 0x9C45;
static const uint16_t encoderRegSpeedH                         = 0x9C46;
static const uint16_t encoderRegSpeedL                         = 0x9C47;
static const uint16_t encoderRegLimitSwitchState               = 0x9C48;
static const uint16_t encoderRegPhysicalSTResolutionH          = 0x9C4D;
static const uint16_t encoderRegPhysicalSTResolutionL          = 0x9C4E;
static const uint16_t encoderRegPhysicalMTResolutionH          = 0x9C4F;
static const uint16_t encoderRegPhysicalMTResolutionL          = 0x9C50;
   
static const uint16_t encoderRegScalingEnabled                 = 0x9C51;
static const uint16_t encoderRegSTResolutionH                  = 0x9C52;
static const uint16_t encoderRegSTResolutionL                  = 0x9C53;
static const uint16_t encoderRegTotResolutionH                 = 0x9C54;
static const uint16_t encoderRegTotResolutionL                 = 0x9C55;
static const uint16_t encoderRegPresetH                        = 0x9C56;
static const uint16_t encoderRegPresetL                        = 0x9C57;
static const uint16_t encoderRegOffsetH                        = 0x9C58;
static const uint16_t encoderRegOffsetL                        = 0x9C59;
static const uint16_t encoderRegCountDirection                 = 0x9C5A;
static const uint16_t encoderRegSpeedMode                      = 0x9C5B;
static const uint16_t encoderRegSpeedFilter                    = 0x9C5C;
static const uint16_t encoderRegLimitSwitchEnable              = 0x9C5D;
static const uint16_t encoderRegLowLimitSwitchH                = 0x9C5E;
static const uint16_t encoderRegLowLimitSwitchL                = 0x9C5F;
static const uint16_t encoderRegHighLimitSwitchH               = 0x9C60;
static const uint16_t encoderRegHighLimitSwitchL               = 0x9C61;
static const uint16_t encoderRegDelay                          = 0x9C62;
static const uint16_t encoderRegErrorencoderReg                = 0x9C63;
static const uint16_t encoderRegDeviceResetStore               = 0x9C63;
static const uint16_t encoderRegParameters                     = 0x9C64;
static const uint16_t encoderRegAutoStore                      = 0x9C65;
static const uint16_t encoderRegRestoreAllParameters           = 0x9C66;
static const uint16_t encoderRegRestoreAplicationParameters    = 0x9C67;
static const uint16_t encoderRegAutoTest                       = 0x9C68;
static const uint16_t encoderRegSoftwareVersion                = 0x9C69;
static const uint16_t encoderRegSerialNumberH                  = 0x9C70;
static const uint16_t encoderRegSerialNumberL                  = 0x9C71;
static const uint16_t encoderRegLifeCycleCounter               = 0x9C72;
static const uint16_t encoderRegRollCounter                    = 0x9C73;
static const uint16_t encoderRegSerialParameters               = 0x9C78;
static const uint16_t encoderRegCommUpdate                     = 0x9C82;
static const uint16_t encoderRegNodeAddress                    = 0x9C83;
static const uint16_t encoderRegNodeUpdate                     = 0x9C84;
static const uint16_t encoderRegAutoBaudEnable                 = 0x9C85;
static const uint16_t encoderRegAutoBaudTimeout                = 0x9C86;
static const uint16_t encoderRegRestoreBusParameteres          = 0x9C87;
static const uint16_t encoderRegTermination                    = 0x9C88;
static const uint16_t encoderRegTermUpdate                     = 0x9C89;
        
