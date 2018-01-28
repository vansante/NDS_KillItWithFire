/*
 * Screen.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <nds.h>
#include "constants.h"


namespace KIWF {

	class Screen {
	private:
		u16* framebuffer;
		u16* buffer;

		u16 bufferStartX;
		u16 bufferStartY;

		bool autoClear;
		bool autoSwap;
	public:
		static const u16 WIDTH = 256;
		static const u16 HEIGHT = 192;
		static const int32 NUM_PIXELS = WIDTH * HEIGHT;
		static const int32 BUFFER_BYTE_SIZE = NUM_PIXELS * sizeof(u16);
		static const u8 DMA_CHANNEL = 3;

		Screen(u16* framebuffer, bool autoClear, bool autoSwap);
		virtual ~Screen();

		void setAutoClear(bool autoClear);
		void setAutoSwap(bool autoSwap);
		bool getAutoSwap();


		void setBufferOrigin(u16 bufferStartX, u16 bufferStartY);

		u16* getBuffer();

		void swapBuffer();
		void clearScreen();
	};
}

#endif /* SCREEN_H_ */
