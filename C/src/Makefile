CC = gcc
 
 all: main.o encoder.o encoderRegisters.o 
	 $(CC) main.o encoder.o encoderRegisters.o -o main
 
 main.o: main.c encoder.h encoderRegisters.h
	$(CC) main.c -c -o main.o 
 
 encoder.o: encoder.c encoder.h encoderPrivate.h encoderRegisters.h
	$(CC) encoder.c -c -o encoder.o
 
 encoderRegisters.o: encoderRegisters.c encoderRegisters.h
	$(CC) encoderRegisters.c -c -o encoderRegisters.o
 
 
	
