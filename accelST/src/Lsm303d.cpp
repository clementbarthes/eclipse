/*
 * Lsm303d.cpp
 *
 *  Created on: May 27, 2016
 *      Author: developer
 */

#include "Lsm303d.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/time.h>


using namespace std;

Lsm303d::Lsm303d() {

	i2Cdevice = new BlackLib::BlackI2C(BlackLib::I2C_1, accelAddress);

	if(!i2Cdevice->open( BlackLib::ReadWrite | BlackLib::NonBlock)){
		std::cout << "I2C DEVICE CAN\'T OPEN.;" << std::endl;
	}
	i2Cdevice->writeByte(0x1F,0x40); // CTRL0 - FIFO enabled
	i2Cdevice->writeByte(0x20,0x77); // CTRL1 - 200Hz ODR for accel
	i2Cdevice->writeByte(0x21,0xC0); // CTRL2 - 50Hz AA - +/-2g accel
	i2Cdevice->writeByte(0x22,0x00); // CTRL3
	i2Cdevice->writeByte(0x23,0x00); // CTRL4
	i2Cdevice->writeByte(0x24,0x74); // CTRL5 - 100Hz ODR for magnetometer
	i2Cdevice->writeByte(0x25,0x00); // CTRL6 - +/-2 gauss scale
	i2Cdevice->writeByte(0x26,0x00); // CTRL7
	i2Cdevice->writeByte(0x2E,0x40); // Stream mode
}

float Lsm303d::readAccel(uint8_t accelDir) {
	uint8_t *accelBytes = new uint8_t[2];

	accelBytes[0] = i2Cdevice->readByte(accelDir);
	accelBytes[1] = i2Cdevice->readByte(accelDir | 0x01);
	int16_t accel;
	memcpy(&accel, accelBytes, 2);
//	std::printf("Accel: 0x%02x%02x \n",accelBytes[1], accelBytes[0]);
//	std::printf("Accel: %d \n",accel);
	return (float)accel*0.00006103888;
}

float Lsm303d::readMagnet(uint8_t magnetDir) {
	union magnetUnion {
		int16_t asInt;
		char asArray[2];
	} magnetVal;

	magnetVal.asArray[0] = i2Cdevice->readByte(magnetDir);
	magnetVal.asArray[1] = i2Cdevice->readByte(magnetDir|0x01);

	return (float)magnetVal.asInt*0.00006103888;
}

Lsm303d::~Lsm303d() {
	// TODO Auto-generated destructor stub
}
