/*
 * main.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "constants.h"
#include "System.h"
#include "SplashMode.h"


using namespace KIWF;

int main() {
#ifdef DEBUG_MODE
	defaultExceptionHandler();
#endif

	Mode* mode = new SplashMode(
		System::getInstance().getVideo(),
		System::getInstance().getInput()
	);

	System::getInstance().setMode(mode);
	System::getInstance().runLoop();

	return 0;
}

