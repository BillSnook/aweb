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
	
	int getI2CReg( int reg );
	void putI2CReg( int reg, int newValue );
	
	char *getUPS2();

};

#endif /* minion_hpp */
