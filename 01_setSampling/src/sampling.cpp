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
#include <unistd.h>
#include <sys/time.h>
using namespace std;

void sigTimer_handler(int signum);

int main() {

	struct itimerval timer;
	/* Initial timeout value */
	timer.it_value.tv_sec = 1;  //in sec
	timer.it_value.tv_usec = 0; // in usec
	/* Repetitive timer */
	timer.it_interval.tv_sec = 1;  //in sec
	timer.it_interval.tv_usec = 0;

	signal(SIGALRM, &sigTimer_handler);
	printf("Timer: %i \n", setitimer(ITIMER_REAL, &timer, NULL));

	for (;;) {
		sleep(1);
	}
	return 0;
}


void sigTimer_handler(int signum){
	printf("Sample now! \n");
}
