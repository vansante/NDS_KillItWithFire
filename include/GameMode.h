/*
 * GameMode.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef GAMEMODE_H_
#define GAMEMODE_H_

#include "Mode.h"
#include "Level.h"
#include "GameUI.h"
#include "SoundManager.h"

namespace KIWF {

	class GameMode : public Mode {
	private:
		Level* level;
		GameUI* gameUI;

	public:
		GameMode(Video* video, Input* input) : Mode(video, input) {
			video->getScreen(MAIN_SCREEN_BACKGROUND)->setAutoClear(false);
			video->clearScreen(MAIN_SCREEN_BACKGROUND);

			video->getScreen(MAIN_SCREEN_FOREGROUND)->setAutoClear(true);

			video->getScreen(TOUCH_SCREEN_FOREGROUND)->setAutoClear(false);
			video->clearScreen(TOUCH_SCREEN_FOREGROUND);
			#ifndef DEBUG_MODE
				video->swapBuffer(TOUCH_SCREEN_FOREGROUND);
			#endif

			SoundManager::getInstance().setMusicVolume(255);
			SoundManager::getInstance().playMusic(MOD_BACKGROUND_MUSIC, MM_PLAY_LOOP);

			this->level = new Level(video);

			this->gameUI = new GameUI(this->level);
		}

		virtual ~GameMode();
		void processInput();
	};
}

#endif /* GAMEMODE_H_ */
