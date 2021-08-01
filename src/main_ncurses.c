#include <modbus/modbus.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "encoder.h"

#define ENCODER1 127


//extern modbus_t *ctx;

int main(void)
{
	int ch = 0;
	char* port = "/dev/ttyUSB0";
	int baud = 57600;
	char parity = 'E';
	int databits = 8;
	int stopbits = 1;

	EncoderInit(port, baud, parity, databits, stopbits);
	//EncoderSetBaudrate(ENCODER1, 8);
	//EncoderSetSpeedMode(ENCODER1,2);
	initscr();
	curs_set(0);
	nocbreak();
	//noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color	*/
	//box(stdscr,0,0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(3));
	mvprintw(1,5, "Press q to exit");
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(2));
	mvprintw(3,5, "MODBUS");
	attroff(COLOR_PAIR(2));

	mvprintw(4,5, "port:");
	mvprintw(5,5, "bauds:");
	mvprintw(6,5, "parity:");
	mvprintw(7,5, "databits:");
	mvprintw(8,5, "stopbits:");

	attron(COLOR_PAIR(2));
	mvprintw(10,5, "ENCODER 1");
	attroff(COLOR_PAIR(2));

	mvprintw(11,5, "Serial Nr:");
	mvprintw(12,5, "Position:");
	mvprintw(13,5, "Actual reverse state:");
	mvprintw(14,5, "Speed:");
	mvprintw(15,5, "Physical ST Resolution:");
	mvprintw(16,5, "Physical MT Resolution:");
	mvprintw(17,5, "ST Resolution:");
	mvprintw(18,5, "Total Resolution:");
	mvprintw(19,5, "Offset:");
	mvprintw(20,5, "Baudrate:");
	mvprintw(21,5, "Angle:");
	mvprintw(24,5, "Termination:");

	attron(COLOR_PAIR(1));
	mvprintw(4,17, "%s", port);
	mvprintw(5,17, "%d", baud);
	mvprintw(6,17, "%c", parity);
    mvprintw(7,17, "%d", databits);
	mvprintw(8,17, "%d", stopbits);

	mvprintw(11,29, "%10u", EncoderGetSerialNumber(ENCODER1));
	mvprintw(13,29, "%s", EncoderGetActualReverseState(ENCODER1) ? "CCW" : "CW" );
	mvprintw(15,29, "%10u", EncoderGetPhysicalSTResolution(ENCODER1));
	mvprintw(16,29, "%10u", EncoderGetPhysicalMTResolution(ENCODER1));
	mvprintw(17,29, "%10u", EncoderGetSTResolution(ENCODER1));
	mvprintw(18,29, "%010u", EncoderGetTotResolution(ENCODER1));
	mvprintw(19,29, "%010u", EncoderGetOffset(ENCODER1));
	mvprintw(20,29, "%u", EncoderGetBaudrate(ENCODER1));
	mvprintw(24,29, "%s", EncoderGetTermination(ENCODER1) ? "ON" : "OFF");
	
	attroff(COLOR_PAIR(1));
	time_t result;
	struct tm * cur_time;
	while((ch = getch()) != 'q')
	{
		attron(COLOR_PAIR(1));
		//mvprintw(6,15, "%u", EncoderGetLifeCycleCounter(ENCODER1));
		//move(12,29);
		//clrtoeol();
		//mvprintw(12,29, "0000000000");
		mvprintw(12,29, "%10u", EncoderGetPosition(ENCODER1));
		angle angle = EncoderGetSTAngle(ENCODER1);
		mvprintw(21,29, "%8.4f", angle.deg);addch(ACS_DEGREE);
		mvprintw(22,29, "%3d", angle.d); addch(ACS_DEGREE); printw(" %02d\' %02d\"", angle.dm, angle.ds);
		mvprintw(23,29, "%3dh %02d\' %02d\"", angle.h, angle.hm, angle.hs);
		mvprintw(14,29, "%10d", EncoderGetSpeed(ENCODER1));
		attroff(COLOR_PAIR(1));
		wmove(stdscr,0,0);
		result = time(NULL);
    	cur_time = localtime(&result);
		mvprintw(0,5,"%s", asctime(cur_time));
		wrefresh(stdscr);

		usleep(100000);
	}
	endwin();
	EncoderClose();
	return 0;
}

