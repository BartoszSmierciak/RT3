CC = gcc

CFLAGSS  = -g -Wall -I/opt/libmodbus/include/ -L/opt/libmodbus/lib/ `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

CFLAGSE  = -lncurses -lmodbus

default: all

all: main.o main_ncurses.o main_gtk.o encoder.o encoderRegisters.o
	$(CC) $(CFLAGSS) main.o encoder.o encoderRegisters.o -o main $(CFLAGSE)
	$(CC) $(CFLAGSS) main_ncurses.o encoder.o encoderRegisters.o -o main_ncurses $(CFLAGSE)
	$(CC) $(CFLAGSS) main_gtk.o encoder.o encoderRegisters.o -o main_gtk $(CFLAGSE)

main.o: main.c encoder.h encoderRegisters.h
	$(CC) $(CFALGSS) -c main.c $(CFLAGSE)

main_ncurses.o: main_ncurses.c encoder.h encoderRegisters.h
	$(CC) $(CFLAGSS) -c main_ncurses.c $(CFLAGSE)

main_gtk.o: main_gtk.c encoder.h encoderRegisters.h
	$(CC) $(CFLAGSS) -c main_gtk.c $(CFLAGSE)

encoder.o: encoder.c encoder.h encoderRegisters.h encoderPrivate.h
	$(CC) $(CFLAGSS) -c encoder.c $(CFLAGSE)

encoderRegisters.o: encoderRegisters.c encoderRegisters.h
	$(CC) $(CFLAGSS) -c encoderRegisters.c $(CFLAGSE)

clean:
	$(RM) all *.o *~

