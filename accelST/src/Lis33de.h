/*
 * Lis33de.h
 *
 *  Created on: Jun 5, 2016
 *      Author: developer
 */

#ifndef LIS33DE_H_
#define LIS33DE_H_

#include <unistd.h>
#include <stdint.h>
#include "BlackLib/BlackI2C/BlackI2C.h"

class Lis33de {
	BlackLib::BlackI2C  *i2Cdevice;
	static const uint8_t accelAddress = 0x1e;
public:
	Lis33de();
	virtual ~Lis33de();
};

#endif /* LIS33DE_H_ */
