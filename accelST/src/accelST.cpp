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
#include "SocketNode.h"
using namespace std;

#define pointsToGather 10

void sigTimer_handler(int signum);

Lsm303d *lsm303d;
ofstream dataFile;
char readBuffer[BUFSIZ+1];
int serverStatus = 0;
SocketNode* socketNode = new SocketNode();
//char refPath[] = "/media/sdcard/data0001.txt";

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
	static int dataGatherIter = 0;
	static int ptrIter = 0;
	static char gatheredData[pointsToGather*(3*sizeof(float))];

	float accX = lsm303d->readAccel(Lsm303d::accelX);
	float accY = lsm303d->readAccel(Lsm303d::accelY);
	float accZ = lsm303d->readAccel(Lsm303d::accelZ);

	++dataGatherIter;
	memcpy(gatheredData+ptrIter, &accX, sizeof(float));
	ptrIter += sizeof(float);
	memcpy(gatheredData+ptrIter, &accY, sizeof(float));
	ptrIter += sizeof(float);
	memcpy(gatheredData+ptrIter, &accZ, sizeof(float));
	ptrIter += sizeof(float);

	if (dataGatherIter == pointsToGather){
		if(!socketNode->writeToNode(gatheredData, pointsToGather*3*sizeof(float))){
			// If it failed, try to reconnect
			printf("Reconnection: %i \n", serverStatus = socketNode->connectToNode());
		}
		dataGatherIter = 0;
		ptrIter = 0;
	}
}
