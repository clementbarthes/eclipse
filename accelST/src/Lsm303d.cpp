/*
 * Lsm303d.cpp
 *
 *  Created on: May 27, 2016
 *      Author: developer
 */

#include "Lsm303d.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
using namespace std;

Lsm303d::Lsm303d() {
	i2c = new I2c(accelAddress);
	i2c->writeReg(0x1F,0x80); // CTRL0 - Reboot
	sleep(1);

	i2c->writeReg(0x1F,0x40); // CTRL0 - FIFO enabled
	i2c->writeReg(0x20,0x77); // CTRL1 - 200Hz ODR for accel
	i2c->writeReg(0x21,0xC0); // CTRL2 - 50Hz AA - +/-2g accel
	i2c->writeReg(0x22,0x00); // CTRL3
	i2c->writeReg(0x23,0x00); // CTRL4
	i2c->writeReg(0x24,0x74); // CTRL5 - 100Hz ODR for magnetometer
	i2c->writeReg(0x25,0x00); // CTRL6 - +/-2 gauss scale
	i2c->writeReg(0x26,0x00); // CTRL7
	i2c->writeReg(0x2E,0x00); // Stream mode

//	i2c->writeReg(0x1F,0x40); // CTRL0 - FIFO enabled
//	i2c->writeReg(0x20,0x77); // CTRL1 - 200Hz ODR for accel
//	i2c->writeReg(0x21,0xC0); // CTRL2 - 50Hz AA - +/-2g accel
//	i2c->writeReg(0x22,0x00); // CTRL3
//	i2c->writeReg(0x23,0x00); // CTRL4
//	i2c->writeReg(0x24,0x74); // CTRL5 - 100Hz ODR for magnetometer
//	i2c->writeReg(0x25,0x00); // CTRL6 - +/-2 gauss scale
//	i2c->writeReg(0x26,0x00); // CTRL7
//	i2c->writeReg(0x2E,0x00); // FIFO-CTRL

}

float Lsm303d::readAccel(uint8_t accelDir) {
	uint8_t *accelBytes = new uint8_t[2];
//	accelBytes = i2c->burstRead(accelDir,2);
	//i2c->setAddress();
	accelBytes[0] = i2c->readReg(accelDir);
	accelBytes[1] = i2c->readReg(accelDir | 0x01);
	int16_t accel;
	memcpy(&accel, accelBytes, 2);
//	std::printf("Accel: 0x%02x%02x \n",accelBytes[1], accelBytes[0]);
	std::printf("Accel: %d \n",accel);
	return 0.00006103888;
}

float Lsm303d::readMagnet(uint8_t magnetDir) {
	union magnetUnion {
		int16_t asInt;
		char asArray[2];
	} magnetVal;

	magnetVal.asArray[0] = i2c->readReg(magnetDir);
	magnetVal.asArray[1] = i2c->readReg(magnetDir|0x01);

	return (float)magnetVal.asInt*0.00006103888;
}

Lsm303d::~Lsm303d() {
	// TODO Auto-generated destructor stub
}
