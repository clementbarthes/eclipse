//============================================================================
// Name        : sampling.cpp
// Author      : Clement Barthes
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <signal.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include<fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const string gpio_filepath = "/sys/class/gpio/";
const string export_File = "export";
const string direction_File= "gpio67/direction";
const string gpio_File = "gpio67/value";

#define GPIO2_ADDR 0x4804C000

#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190
#define pin67 (1<<24)

volatile unsigned int *gpio_addr;
volatile unsigned int *gpio_setdataout_addr;
volatile unsigned int *gpio_cleardataout_addr;


void sigTimer_handler(int signum);

int main() {

	int fd = open("/dev/mem", O_RDWR);
	gpio_addr = (unsigned int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_ADDR);

	gpio_setdataout_addr   = gpio_addr + GPIO_SETDATAOUT;
	gpio_cleardataout_addr = gpio_addr + GPIO_CLEARDATAOUT;


	struct itimerval timer;
	/* Initial timeout value */
	timer.it_value.tv_sec = 1;  //in sec
	timer.it_value.tv_usec = 0; // in usec
	/* Repetitive timer */
	timer.it_interval.tv_sec = 0;  //in sec
	timer.it_interval.tv_usec = 100000;

	signal(SIGALRM, &sigTimer_handler);
	printf("Timer: %i \n", setitimer(ITIMER_REAL, &timer, NULL));

	for (;;) {
		sleep(1);
	}
	return 0;
}


void sigTimer_handler(int signum){
	static bool flipFlop = 0;
	flipFlop = !flipFlop;
	if(flipFlop){
		*gpio_setdataout_addr = pin67;
	} else {
		*gpio_cleardataout_addr = pin67;
	}


}
