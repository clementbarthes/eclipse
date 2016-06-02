/*
 * Lsm303d.h
 *
 *  Created on: May 27, 2016
 *      Author: developer
 */

#ifndef LSM303D_H_
#define LSM303D_H_


#include <unistd.h>
#include <stdint.h>
#include "BlackLib/BlackI2C/BlackI2C.h"


class Lsm303d {
	BlackLib::BlackI2C  *i2Cdevice;
	static const uint8_t accelAddress = 0x1e;

public:
	static const uint8_t accelX = 0x28;
	static const uint8_t accelY = 0x2A;
	static const uint8_t accelZ = 0x2C;

	static const uint8_t magnetX = 0x08;
	static const uint8_t magnetY = 0x0A;
	static const uint8_t magnetZ = 0x0C;

	float readAccel(uint8_t accelDir);
	float readMagnet(uint8_t magnetDir);

	Lsm303d();
	virtual ~Lsm303d();
};


#endif /* LSM303D_H_ */
