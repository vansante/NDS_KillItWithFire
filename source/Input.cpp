/*
 * Input.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "Input.h"

namespace KIWF {

	Input::Input() {

	}

	Input::~Input() {}


	void Input::fetchInput() {
		// Read key events
		scanKeys();

		// Store keys
		this->_keysDown = keysDown();
		this->_keysUp = keysUp();
		this->_keysHeld = keysHeld();

		// Read screen touch position
		touchRead(this->_touchPos);
	}

	u16 Input::getKeysDown() {
		return this->_keysDown;
	}

	u16 Input::getKeysUp() {
		return this->_keysUp;
	}

	u16 Input::getKeysHeld() {
		return this->_keysHeld;
	}

	u16 Input::getTouchX() {
		return this->_touchPos->px;
	}

	u16 Input::getTouchY() {
		return this->_touchPos->py;
	}
}
