/*
 * I2c.cpp
 *
 *  Created on: May 17, 2016
 *      Author: root
 */

#include "I2c.h"
#include<iostream>
#include<sstream>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<iomanip>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
using namespace std;

I2c::I2c(uint8_t devAddress) {
	this->devAddress = devAddress;
	// Open the bus
	const string filename = "/dev/i2c-1";
	fileHandle = open(filename.c_str(),O_RDWR);
	ioctl(fileHandle,I2C_SLAVE,this->devAddress);
}

uint8_t I2c::readReg(uint8_t reg) {
	uint8_t rxBuffer[1];
	uint8_t txBuffer[1];
	txBuffer[0] = reg;
	ioctl(fileHandle,I2C_SLAVE,this->devAddress);
	write(fileHandle,txBuffer,1);
	read(fileHandle,rxBuffer,1);
	return rxBuffer[0];

}
uint8_t* I2c::burstRead(uint8_t reg, int nBytes) {
	uint8_t* rxBuffer = new uint8_t[nBytes];
	uint8_t txBuffer[1];
	txBuffer[0] = reg;
	ioctl(fileHandle,I2C_SLAVE,this->devAddress);
	write(fileHandle,txBuffer,1);
	if(read(fileHandle,rxBuffer,nBytes)!=nBytes){
		perror("I2c failed");
	}
	return rxBuffer;
}


void I2c::writeReg(uint8_t reg, uint8_t value) {
	uint8_t txBuffer[2];
	txBuffer[0] = reg;
	ioctl(fileHandle,I2C_SLAVE,this->devAddress);
	write(fileHandle,txBuffer,2);
	return;
}

void I2c::setAddress() {
	ioctl(fileHandle,I2C_SLAVE,this->devAddress);
}


I2c::~I2c() {
	// TODO Auto-generated destructor stub
}

