/*
 * I2c.h
 *
 *  Created on: May 17, 2016
 *      Author: root
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>


class I2c {
	uint8_t devAddress;
	int fileHandle;
public:
	I2c(uint8_t devAddress);
	void setAddress();
	uint8_t readReg(uint8_t reg);
	uint8_t *burstRead(uint8_t reg, int nBytes);
	void writeReg(uint8_t reg, uint8_t value);
	virtual ~I2c();
};

#endif /* I2C_H_ */
