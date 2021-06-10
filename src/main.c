#include <stdio.h>
#include <modbus/modbus.h>
#include "encoder.h"
//#include "encoderRegisters.h"



int main()
{
	EncoderInit("/dev/ttyUSB0", 19200 , 'N', 8, 1);
	printf("Azymut [imp]: %d\n", EncoderGetPosition(127));
	//printf("Elewacja [imp]: %d\n", EncoderGetPosition(126));

	EncoderClose();
	return 0;
}
