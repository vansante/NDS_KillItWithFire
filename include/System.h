/*
 * System.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <nds.h>
#include <stdio.h>

#include "Video.h"
#include "Input.h"
#include "Mode.h"

namespace KIWF {

	class System {
	private:
		static System* instance;

		System();
		System(System const&);			// Don't Implement
		void operator=(System const&); 	// Don't implement

		Video* video;
		Input* input;
		Mode* mode;

	public:
		virtual ~System();

		static System& getInstance() {
			static System instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}

		void runLoop();
		void setMode(Mode* mode);
		Video* getVideo();
		Input* getInput();

		static bool dmaCopySafe(const void *src, void *dst, u32 size);
		static bool dmaFillSafe(u32 fill, void *dst, u32 size);
	};
}

#endif /* SYSTEM_H_ */
