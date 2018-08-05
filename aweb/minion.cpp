//
//  minion.cpp
//  cweb
//
//  Created by William Snook on 4/28/18.
//  Copyright © 2018 billsnook. All rights reserved.
//

#include <unistd.h>			// close read write
#include <stdio.h>			// printf
#include <fcntl.h>			// open
#include <sys/ioctl.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>

#include "minion.hpp"

//  SBC HAT - GPIO-controlled
//  Raspi UPS HAT V1.0
#define VREG 2
#define CREG 4
#define BUFSIZE	16
#define DEV "/dev/i2c-1"
#define ADRS 0x36


Minion::Minion() {
	
}

bool Minion::setupMinion( int i2cAddr ) {
	
	pi2c = i2cAddr;
#ifdef ON_PI
	int device = wiringPiI2CSetup( pi2c );
	if ( device < 0 ) {
		syslog(LOG_NOTICE, "Failed opening I2C device at address: %d", pi2c);
		return false;
	}
	syslog(LOG_NOTICE, "Opened I2C device at address: %d, device number: %d", pi2c, device);
#endif  // ON_PI

	return true;
}

bool Minion::resetMinion() {
	
	return true;
}

int Minion::getI2CReg() {
	
	int rdValue = 0;
#ifdef ON_PI
	rdValue = wiringPiI2CRead(pi2c);
#endif  // ON_PI
	return rdValue;
}

void Minion::putI2CReg( int newValue ) {
	
#ifdef ON_PI
	wiringPiI2CWrite(pi2c, newValue);
#endif  // ON_PI
}

int Minion::testRead() {
	
	int got = 0;
#ifdef ON_PI
	got = getI2CReg();
	syslog(LOG_NOTICE, "Read 0x%X from I2C device", got);
#endif // ON_PI
	
	return got;
}

void Minion::testWrite(int data) {
	
	putI2CReg(data);

}
