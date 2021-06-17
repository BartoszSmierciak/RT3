#include <stdio.h>
#include <modbus/modbus.h>
#include "encoder.h"
#include <time.h>

#define ENCODER1 127

extern modbus_t *mb;

int main()
{

	EncoderInit("/dev/ttyUSB0", 19200, 'E', 8, 1);
	EncoderPrintRegisters(ENCODER1);
	EncoderClose();
	return 0;
}
