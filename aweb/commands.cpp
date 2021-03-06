//
//  commands.cpp
//  cweb
//
//  Created by William Snook on 4/21/18.
//  Copyright © 2018 billsnook. All rights reserved.
//

#include "commands.hpp"

#include "listen.hpp"
#include "threader.hpp"
#include "minion.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>


#define bufferSize	256

//#define aWaitOn		500000
#define xWaitOn		100000
#define xWaitOff	50000
#define tokenMax	4

Commander	commander;
//Hardware	hardware;

//extern Filer	filer;
extern Listener	listener;
extern Minion minion;

void Commander::setupCommander() {
	
	syslog(LOG_NOTICE, "In setupCommander" );
//	hardware = Hardware();
//	hardware.setupForDCMotors();
}

void Commander::serviceCommand( char *command, int socket ) {	// Main command determination routine

	syslog(LOG_NOTICE, "In commandLoop with: %s", command );
	int len = int( strlen( command ) );
	char *nextToken[tokenMax+1];
	int i = 0;
	int t = 0;
	do {
		nextToken[t] = &command[i];
		t++;
		do {
			i++;
		} while ( ( i < len ) && ( command[i] != ' ' ) && ( command[i] != '\n' ) && ( command[i] != 0 ) );
		command[i] = 0;
		i++;
	} while ( ( i < len ) && ( t < tokenMax ) );
	int tokenCount = t;
	int token1 = 0;
	int token2 = 0;
	if ( tokenCount > 1 ) {
		token1 = std::atoi( nextToken[1] );
	}
	if ( tokenCount > 2 ) {
		token2 = std::atoi( nextToken[2] );
	}
	char first = command[0];	// Get command

	for ( int y = 0; y < tokenCount; y++ ) {
		syslog(LOG_NOTICE, "Token %d: %s", y, nextToken[y] );
	}

	char *msg = (char *)malloc( 1024 );
	memset( msg, 0, 1024 );
	memcpy( msg, "\nAck\n", 5 );
	switch ( first ) {
			
		case 'A':
		case 'a': {
			int data = minion.testRead();
			syslog(LOG_NOTICE, "Read data: %d", data );
			usleep(1000000);
		}
			break;

		case 'B':
		case 'b': {
			minion.testWrite( 0x44 );
			syslog(LOG_NOTICE, "Wrote data" );
			usleep(1000000);
		}
			break;

		case 'C':
		case 'c':
			break;

		case 'D':
		case 'd':
			break;


			
//		case 'A':
//		case 'a':
//			hardware.setMtrDirSpd( 0, 1, token1 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 0, 0 );
//			break;
//
//		case 'B':
//		case 'b':
//			hardware.setMtrDirSpd( 0, 0, token1 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 0, 0 );
//			break;
//
//		case 'C':
//		case 'c':
//			hardware.setMtrDirSpd( 1, 1, token1 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 1, 0 );
//			break;
//
//		case 'D':
//		case 'd':
//			hardware.setMtrDirSpd( 1, 0, token1 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 1, 0 );
//			break;
//
//		case 'E':
//		case 'e':
//			hardware.setMtrDirSpd( 0, 1, token1 );
//			hardware.setMtrDirSpd( 1, 1, token2 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 0, 0 );
//			hardware.setMtrSpd( 1, 0 );
//			break;
//
//		case 'F':
//		case 'f':
//			hardware.setMtrDirSpd( 1, 0, token1 );
//			hardware.setMtrDirSpd( 1, 0, token2 );
//			usleep( aWaitOn );
//			hardware.setMtrSpd( 0, 0 );
//			hardware.setMtrSpd( 1, 0 );
//			break;
//
//		case 'G':
//		case 'g':
//			syslog(LOG_NOTICE, "Command g calls: hardware.cmdSpd( %d )", token1 );
//			hardware.cmdSpd( token1 );
//			break;
//
//		case 'H':
//		case 'h':
//		{
//			char *display = hardware.speed.displaySpeedArray();
//			syslog(LOG_NOTICE, "displaySpeedArray():\n%s", display );
//			memcpy( msg, display, strlen( display ) );
//			free( display );
//		}
//			break;
//
//		case 'I':
//		case 'i':
//			filer.readData( hardware.speed.forward, hardware.speed.reverse );
//			memcpy( msg, "\nData read\n", 11 );
//			break;
//
//		case 'J':
//		case 'j':
//		{
//			char *display = hardware.speed.setSpeedTestIndex( token1 );
//			memcpy( msg, display, strlen( display ) );
//			free( display );
//		}
//			break;
//
//		case 'K':
//		case 'k':
//			hardware.speed.setSpeedRight( token1 );
//			break;
//
//		case 'L':
//		case 'l':
//			hardware.speed.setSpeedLeft( token1 );
//			break;
//
////		case 'R':
////		case 'r':
////			filer.readData( hardware.speed.forward, hardware.speed.reverse );
////			break;
//
//		case 'S':
//		case 's':
//			hardware.cmdSpd( 0 );
//			break;
//		// Test case for app feature - send response, wait 5 seconds, send another
//		case 'T':
//		case 't':
//			memcpy( msg, "\nMessage 1...\n", 15 );
//			listener.writeBack( msg, socket );
//			usleep( 5000000 ); // 5 second delay
//			memcpy( msg, "\nMessage 2   \n", 15 );
//			break;
//
//		case 'U':
//		case 'u':	// Set forward array based on index 1 and index 8
//			hardware.speed.setSpeedForward();
//			break;
//
//		case 'V':
//		case 'v':	// Set reverse array based on index -1 and index -8
//			hardware.speed.setSpeedReverse();
//			break;
//
//		case 'W':
//		case 'w':
//			filer.saveData( hardware.speed.forward, hardware.speed.reverse );
//			break;
//
//		case 'X':
//		case 'x':
//			for ( int i = 0; i < 3; i++ ) {
//				hardware.setMtrDirSpd( 1, 1, token1 );
//				usleep( xWaitOn );
//				hardware.setMtrDirSpd( 1, 1, 0 );
//				usleep( xWaitOff );
//				hardware.setMtrDirSpd( 1, 0, token1 );
//				usleep( xWaitOn );
//				hardware.setMtrDirSpd( 1, 0, 0 );
//				usleep( xWaitOff );
//				hardware.setMtrDirSpd( 0, 1, token1 );
//				usleep( xWaitOn );
//				hardware.setMtrDirSpd( 0, 1, 0 );
//				usleep( xWaitOff );
//				hardware.setMtrDirSpd( 0, 0, token1 );
//				usleep( xWaitOn );
//				hardware.setMtrDirSpd( 0, 0, 0 );
//				usleep( xWaitOff );
//			}
//			break;
//
//		case 'Z':
//		case 'z':
//			sprintf(msg, "@ %d %d %d \n", SPEED_ARRAY, SPEED_ADJUSTMENT, SPEED_ADJUSTMENT * 2 );
//			break;
//
		default:
//			usleep( 10000000 ); // 10 second delay
			break;
	}
	if ( strlen(msg) > 0 ) {
		listener.writeBack( msg, socket );
	}
	free( msg );
}
