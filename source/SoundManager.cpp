/*
 * SoundManager.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "SoundManager.h"

namespace KIWF {

	SoundManager::SoundManager() {
		mmInitDefaultMem((mm_addr)SOUNDBANK_bin);
	}

	SoundManager::~SoundManager() {}

	void SoundManager::playSound(u16 soundId) {
		mmLoadEffect(soundId);
		mmEffectVolume(soundId, 255);
		mmEffect(soundId);
	}

	void SoundManager::pauseSound(u16 soundId) {

	}

	void SoundManager::resumeSound(u16 soundId) {

	}

	void SoundManager::freeSound(u16 soundId) {

	}

	void SoundManager::playMusic(u16 musicId, mm_pmode mode) {
		mmLoad(musicId);
		mmStart(musicId, mode);
	}

	void SoundManager::stopMusic() {
		mmStop();
	}

	void SoundManager::setMusicVolume(u16 volume) {
		if (volume > 1024) {
			volume = 1024;
		}
		mmSetModuleVolume(volume);
	}
}
