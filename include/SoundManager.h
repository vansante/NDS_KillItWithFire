/*
 * SoundManager.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <nds.h>
#include <maxmod9.h>    // Maxmod definitions for ARM9
#include "SOUNDBANK.h"  // Soundbank definitions
#include "SOUNDBANK_bin.h"

namespace KIWF {

	class SoundManager {
	public:
		// Sound volumes
		const static u8 VOLUME_MAX = 127;
		const static u8 VOLUME_HALF = 64;
		const static u8 VOLUME_OFF = 0;

		// Sound panning
		const static u8 PANNING_LEFT = 0;
		const static u8 PANNING_CENTER = 64;
		const static u8 PANNING_RIGHT = 127;
	private:
		static SoundManager* instance;

		SoundManager();
		SoundManager(SoundManager const&);	// Don't Implement
		void operator=(SoundManager const&); 	// Don't implement

	public:
		virtual ~SoundManager();

		static SoundManager& getInstance() {
			static SoundManager instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}

		void playSound(u16 soundId);

		void pauseSound(u16 soundId);

		void resumeSound(u16 soundId);

		void loadSound(u16 soundId);

		void freeSound(u16 soundId);

		void playMusic(u16 musicId, mm_pmode mode);

		void stopMusic();

		void setMusicVolume(u16 volume);
	};
}

#endif /* SOUNDMANAGER_H_ */
