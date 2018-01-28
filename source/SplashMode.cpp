/*
 * SplashMode.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "SplashMode.h"

namespace KIWF {

	SplashMode::~SplashMode() {}

	void SplashMode::processInput() {
		u16 keys = this->input->getKeysDown();

		if (keys & KEY_A) {
			this->switchToGame();
		}
	}

	void SplashMode::switchToGame() {
		SoundManager::getInstance().playSound(SFX_BUTTON_CLICK);

		Mode* mode = new GameMode(this->video, this->input);

		System::getInstance().setMode(mode);
	}
}
