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
volatile int record = 0;
char refPath[255] = "/media/uSD/";

int main() {
	lsm303d = new Lsm303d();
	struct itimerval timer;
	/* Initial timeout value */
	timer.it_value.tv_sec = 1;  //in sec
	timer.it_value.tv_usec = 0; // in usec
	/* Repetitive timer */
	timer.it_interval.tv_sec = 0;  //in sec
	timer.it_interval.tv_usec = 10000;


	signal(SIGALRM, &sigTimer_handler);
	printf("Timer: %i \n", setitimer(ITIMER_REAL, &timer, NULL));

	for (;;) {
		if( int nbytes = socketNode->readFromNode(readBuffer)){
				printf("\n");
				if (readBuffer[0] == 0x52){  //R character, triggers recording
					if (record){
						record = 0;
						dataFile.close();
					} else {
						write(1, readBuffer+1, nbytes-1);
						record = 1;
						dataFile.open(readBuffer+1, ios::app);
						usleep(1000);
					}
				}
			}
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
	if (record){
		dataFile << accX << "\t" << accY << "\t" << accZ <<  "\n";
	}

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
