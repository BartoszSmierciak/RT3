CC = gcc-6
CFLAGS  = -g -Wall -lmodbus `pkg-config --cflags --libs libmodbus`

default: all

all: main.o encoder.o encoderRegisters.o 
	$(CC) $(CFLAGS) main.o encoder.o encoderRegisters.o -o main
 
main.o: main.c encoder.h encoderRegisters.h
	$(CC) $(CFLAGS) -c main.c
 
encoder.o: encoder.c encoder.h encoderRegisters.h encoderPrivate.h
	$(CC) $(CFLAGS) -c encoder.c
 
encoderRegisters.o: encoderRegisters.c encoderRegisters.h
	$(CC) $(CFLAGS) -c encoderRegisters.c
	
clean: 
	$(RM) all *.o *~
 
	
