//
//  minion.hpp
//  cweb
//
//  Created by William Snook on 4/28/18.
//  Copyright © 2018 billsnook. All rights reserved.
//

#ifndef minion_hpp
#define minion_hpp

#ifdef ON_PI

#include <wiringPi.h>
#include <linux/i2c-dev.h>
#include <wiringPiI2C.h>

#endif  // ON_PI


class Minion {

	int	pi2c;

public:
	explicit Minion();

	bool setupMinion( int i2CAddr );
	bool resetMinion();

	int getI2CReg();
	void putI2CReg( int newValue );
	
	int	testRead();
	void testWrite(int data);

};

#endif /* minion_hpp */
