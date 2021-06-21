#include <stdio.h>
#include <modbus/modbus.h>
#include "encoder.h"

#define ENCODER1 127

extern modbus_t *ctx;

int main()
{

	//EncoderInit("/dev/ttyUSB0", 19200, 'E', 8, 1);
	EncoderInit("/dev/ttyUSB0", 9600, 'N', 8, 1);
	printf("inventer: %u\n", EncoderReadModbus(1, 0xA215));
	//EncoderPrintRegisters(ENCODER1);
	EncoderClose();
	return 0;
}
