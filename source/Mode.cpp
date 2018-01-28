/*
 * Mode.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "Mode.h"

namespace KIWF {

	Mode::Mode(Video* video, Input* input) {
		this->video = video;
		this->input = input;
	}

	Mode::~Mode() {}
}
