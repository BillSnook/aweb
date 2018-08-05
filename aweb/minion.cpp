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

int Minion::getI2CReg( int reg ) {
	
	int rdValue = 0;
#ifdef ON_PI
	rdValue = wiringPiI2CReadReg16 (pi2c, reg);
#endif  // ON_PI
	return rdValue;
}

void Minion::putI2CReg( int reg, int newValue ) {
	
#ifdef ON_PI
	wiringPiI2CWriteReg16 (pi2c, reg, newValue);
#endif  // ON_PI
}

char *Minion::testRead() {
	
	char *statsV = (char *)malloc( 32 );

//#ifdef ON_PI
//	char statsC[64];
//	pi2c = wiringPiI2CSetup( ADRS );
//
//	int v = getI2CReg( VREG );
//	int lo = (v >> 8) & 0x00FF;
//	int hi = (v << 8) & 0xFF00;
//	v = hi + lo;
//	sprintf( statsV, "%fV (%d) ",(((float)v)* 78.125 / 1000000.0), v);
//
//	int c = getI2CReg( CREG );
//	close( pi2c );
//
//	lo = (c >> 8) & 0x00FF;
//	hi = (c << 8) & 0xFF00;
//	c = hi + lo;
//	sprintf( statsC, "%f%% (%d)",(((float)c) / 256.0), c);
//	strcat( statsV, statsC );
	
	//
	putI2CReg( 0, 0x41 );
	
	usleep( 1 );
	
	int got = getI2CReg( 1 );
//	syslog(LOG_NOTICE, "Read %d from I2C device", got);
	statsV[0] = got;
	statsV[1] = 0x0A;

//#endif // ON_PI
	
	return statsV;
}

void Minion::testWrite(char *data) {

}
