//============================================================================
// Name        : accelST.cpp
// Author      : Clement Barthes
// Version     :
// Copyright   : This code is not intended to be distributed
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <signal.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/time.h>
#include "Lsm303d.h"
using namespace std;

void sigTimer_handler(int signum);

Lsm303d *lsm303d;

int main() {
	lsm303d = new Lsm303d();
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
	lsm303d->readAccel(Lsm303d::accelX);
	lsm303d->readAccel(Lsm303d::accelY);
	lsm303d->readAccel(Lsm303d::accelZ);
//	printf("X: %f, Y: %f, Z:%f \n", lsm303d->readAccel(Lsm303d::accelX),
//			lsm303d->readAccel(Lsm303d::accelY), lsm303d->readAccel(Lsm303d::accelZ));
}
