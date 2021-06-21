#include <stdio.h>
#include <modbus/modbus.h>
#include <stdlib.h>
#include <ncurses.h>
#include "encoder.h"

#define ENCODER1 127

//extern modbus_t *ctx;

int main()
{
	EncoderInit("/dev/ttyUSB0", 19200, 'E', 8, 1);
	initscr();			/* Start curses mode 		*/
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wprintw(stdscr, "Encoder1: ");
	attron(COLOR_PAIR(1));
	wprintw(stdscr, "%u", EncoderGetPosition(ENCODER1));
	attroff(COLOR_PAIR(1));
    	getch();
	endwin();


	//printf("inventer: %u\n", EncoderReadModbus(1, 0xA215));
	//EncoderPrintRegisters(ENCODER1);
	EncoderClose();
	return 0;
}
