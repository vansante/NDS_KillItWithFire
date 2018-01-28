/*
 * SplashMode.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef SPLASHMODE_H_
#define SPLASHMODE_H_

#include <nds.h>

#include "System.h"
#include "Mode.h"
#include "GameMode.h"
#include "Video.h"
#include "Input.h"
#include "SpriteManager.h"
#include "SoundManager.h"

namespace KIWF {

	class SplashMode : public Mode {
	public:
		SplashMode(Video* video, Input* input) : Mode(video, input) {
			this->video->clearScreen(MAIN_SCREEN_BACKGROUND);
			this->video->drawSprite(MAIN_SCREEN_BACKGROUND, true, 0, 0, SpriteManager::getInstance().get(TITLE_SCREEN_SPRITE));

			SoundManager::getInstance().playSound(SFX_TITLE_SCREEN_INTRO);

			this->video->clearScreen(TOUCH_SCREEN_FOREGROUND);
			this->video->drawSprite(TOUCH_SCREEN_FOREGROUND, true, 0, 0, SpriteManager::getInstance().get(CREDITS_SCREEN_SPRITE));
			#ifndef DEBUG_MODE
				this->video->swapBuffer(TOUCH_SCREEN_FOREGROUND);
			#endif
		}

		virtual ~SplashMode();
		void processInput();
		void switchToGame();
	};
}

#endif /* SPLASHMODE_H_ */
