CC = gcc-6

CFLAGSS  = -g -Wall -lmodbus `pkg-config --cflags --libs libmodbus`

CFLAGSE  = -lncurses

default: all

all: main.o main_ncurses.o encoder.o encoderRegisters.o
	$(CC) $(CFLAGSS) main.o encoder.o encoderRegisters.o -o main
	$(CC) $(CFLAGSS) main_ncurses.o encoder.o encoderRegisters.o -o main_ncurses $(CFLAGSE)

main.o: main.c encoder.h encoderRegisters.h
	$(CC) $(CFALGSS) -c main.c

main_ncurses.o: main_ncurses.c encoder.h encoderRegisters.h
	$(CC) $(CFLAGSS) -c main_ncurses.c $(CFLAGSE)

encoder.o: encoder.c encoder.h encoderRegisters.h encoderPrivate.h
	$(CC) $(CFLAGSS) -c encoder.c

encoderRegisters.o: encoderRegisters.c encoderRegisters.h
	$(CC) $(CFLAGSS) -c encoderRegisters.c

clean:
	$(RM) all *.o *~

