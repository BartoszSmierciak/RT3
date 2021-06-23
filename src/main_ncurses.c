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
	int baud = 19200;
	char parity = 'E';
	int databits = 8;
	int stopbits = 1;

	EncoderInit(port, baud, parity, databits, stopbits);
	//EncoderSetBaudrate(ENCODER1, 5);
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
	box(stdscr,0,0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(3));
	mvprintw(1,1, "Press q to exit");
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

	attron(COLOR_PAIR(1));
	mvprintw(4,17, "%s", port);
	mvprintw(5,17, "%d", baud);
	mvprintw(6,17, "%c", parity);
        mvprintw(7,17, "%d", databits);
	mvprintw(8,17, "%d", stopbits);

	mvprintw(11,29, "%u", EncoderGetSerialNumber(ENCODER1));
	mvprintw(13,29, "%s", EncoderGetActualReverseState(ENCODER1) ? "CCW" : "CW" );
	mvprintw(15,29, "%u", EncoderGetPhysicalSTResolution(ENCODER1));
	mvprintw(16,29, "%u", EncoderGetPhysicalMTResolution(ENCODER1));
	mvprintw(17,29, "%u", EncoderGetSTResolution(ENCODER1));
	mvprintw(18,29, "%u", EncoderGetTotResolution(ENCODER1));
	mvprintw(19,29, "%u", EncoderGetOffset(ENCODER1));
	mvprintw(20,29, "%u", EncoderGetBaudrate(ENCODER1));
	attroff(COLOR_PAIR(1));
	time_t result;
	struct tm * cur_time;
	while((ch = getch()) != 'q')
	{
		attron(COLOR_PAIR(1));
		//mvprintw(6,15, "%u", EncoderGetLifeCycleCounter(ENCODER1));
		mvprintw(12,29, "%u", EncoderGetPosition(ENCODER1));
		mvprintw(14,29, "%u", EncoderGetSpeed(ENCODER1));
		attroff(COLOR_PAIR(1));
		wmove(stdscr,0,0);
		result = time(NULL);
    		cur_time = localtime(&result);
    		//mvprintw(0,5,"%02d:%02d:%02d",cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);
		mvprintw(0,5,"%s", asctime(cur_time));
		wrefresh(stdscr);

		usleep(100000);
	}
	endwin();
	EncoderClose();
	return 0;
}
