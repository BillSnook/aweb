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

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#ifdef ON_PI
#include "/usr/include/linux/i2c-dev.h"		//Needed for I2C port
#endif  // ON_PI

#include "minion.hpp"

//  SBC HAT - GPIO-controlled
//  Raspi UPS HAT V1.0
//#define VREG 2
//#define CREG 4
//#define BUFSIZE	16
#define DEV "/dev/i2c-1"
//#define ADRS 0x36


Minion::Minion() {
	
}

bool Minion::setupMinion( int i2cAddr ) {
	
	pi2c = i2cAddr;
	
#ifdef ON_PI
	
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return false;
	}
	
	if (ioctl(file_i2c, I2C_SLAVE, pi2c) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return false;
	}
//	syslog(LOG_NOTICE, "Opened %s on device %d", filename, file_i2c);

#endif  // ON_PI
	
#ifdef ON_PIX
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

#ifdef ON_PI
	unsigned char buffer[20] = {0};
	int length;

	//----- READ BYTES -----
	length = 4;			// Number of bytes to read
	if (read(file_i2c, buffer, length) != length) {		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
		
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
		return -1;
	} else {
		printf("Data read: %s\n", buffer);
		return buffer[0];
	}
#else	// Else not ON_PI
	return 0;
#endif  // ON_PI

#ifdef ON_PIX
	int rdValue = 0;
	rdValue = wiringPiI2CRead(pi2c);
	return rdValue;
#endif  // ON_PIX
}

void Minion::putI2CReg( int newValue ) {

#ifdef ON_PI
	unsigned char buffer[20] = {0};
	int length;

	//----- WRITE BYTES -----
	buffer[0] = 0x01;
	buffer[1] = newValue;
	length = 2;			//  Number of bytes to write
	if (write(file_i2c, buffer, length) != length) {		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
		
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
	}
#endif  // ON_PI

#ifdef ON_PIX
	wiringPiI2CWrite(pi2c, newValue);
#endif  // ON_PIX
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
