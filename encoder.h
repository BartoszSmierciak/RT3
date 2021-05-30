class Encoder
{
    public:
    
        Encoder();
    
        int GetPosition();
        
        int GetScalingEnabled();
        void SetScalingEnabled(int scalingEnabled);
    
    private:
    
        int _position;
        
        static const uint16_t regPositionH                = 0x9C42;
        static const uint16_t regPositionL                = 0x9C43;
        static const uint16_t regActualReverseState       = 0x9C44;
        static const uint16_t regTermResetState           = 0x9C45;
        static const uint16_t regSpeedH                   = 0x9C46;
        static const uint16_t regSpeedL                   = 0x9C47;
        static const uint16_t regLimitSwitchState         = 0x9C48;
        static const uint16_t regPhysicalSTResolutionH    = 0x9C4D;
        static const uint16_t regPhysicalSTResolutionL    = 0x9C4E;
        static const uint16_t regPhysicalMTResolutionH    = 0x9C4F;
        static const uint16_t regPhysicalMTResolutionL    = 0x9C50;
   
        static const uint16_t regScalingEnabled           = 0x9C51;
        static const uint16_t regSTResolutionH            = 0x9C52;
        static const uint16_t regSTResolutionL            = 0x9C53;
        static const uint16_t regTotResolutionH           = 0x9C54;
        static const uint16_t regTotResolutionL           = 0x9C55;
        static const uint16_t regPresetH                  = 0x9C56;
        static const uint16_t regPresetL                  = 0x9C57;
        static const uint16_t regOffsetH                  = 0x9C58;
        static const uint16_t regOffsetL                  = 0x9C59;
        static const uint16_t regCountDirection           = 0x9C5A;
        static const uint16_t regSpeedMode                = 0x9C5B;
        static const uint16_t regSpeedFilter              = 0x9C5C;
        static const uint16_t regLimitSwitchEnable        = 0x9C5D;
        static const uint16_t regLowLimitSwitchH          = 0x9C5E;
        static const uint16_t regLowLimitSwitchL          = 0x9C5F;
        static const uint16_t regHighLimitSwitchH         = 0x9C60;
        static const uint16_t regHighLimitSwitchL         = 0x9C61;
        static const uint16_t regDelay                    = 0x9C62;
        static const uint16_t regerrorReg                 = 0x9C63;
        static const uint16_t regDeviceResetStore         = 0x9C63;
        static const uint16_t regParameters               = 0x9C64;
        static const uint16_t regAutoStore                = 0x9C65;
        static const uint16_t regRestoreAllParameters     = 0x9C66;
        static const uint16_t regRestoreAplicationParameters = 0x9C67;
        static const uint16_t regAutoTest                 = 0x9C68;
        static const uint16_t regSoftwareVersion          = 0x9C69;
        static const uint16_t regSerialNumberH            = 0x9C70;
        static const uint16_t regSerialNumberL            = 0x9C71;
        static const uint16_t regLifeCycleCounter         = 0x9C72;
        static const uint16_t regRollCounter              = 0x9C73;
        static const uint16_t regSerialParameters         = 0x9C78;
        static const uint16_t regCommUpdate               = 0x9C82;
        static const uint16_t regNodeAddress              = 0x9C83;
        static const uint16_t regNodeUpdate               = 0x9C84;
        static const uint16_t regAutoBaudEnable           = 0x9C85;
        static const uint16_t regAutoBaudTimeout          = 0x9C86;
        static const uint16_t regRestoreBusParameteres    = 0x9C87;
        static const uint16_t regTermination              = 0x9C88;
        static const uint16_t regTermUpdate               = 0x9C89;
        
};
        
       
