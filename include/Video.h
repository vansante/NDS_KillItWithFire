/*
 * Video.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include <nds.h>

#include "Screen.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "SpriteRegion.h"

// Backgound memory block definitions
#define _MAIN_SCREEN_BACKGROUND			((u16*)BG_BMP_RAM(0))
#define _MAIN_SCREEN_FOREGROUND			((u16*)BG_BMP_RAM(6))
#define _TOUCH_SCREEN_FOREGROUND		((u16*)BG_BMP_RAM_SUB(0))

namespace KIWF {

	typedef enum {
		MAIN_SCREEN_BACKGROUND,
		MAIN_SCREEN_FOREGROUND,
		TOUCH_SCREEN_FOREGROUND
	} ScreenId;

	class Video {
	public:
		static const u8 NUM_SCREENS = 3;
		static const u16 VISIBILITY_BIT = (1 << 15);
		static const u8 DMA_CHANNEL = 2;
	private:
		Screen* screens[NUM_SCREENS];
	public:
		Video();
		virtual ~Video();

		void swapBuffers();
		void initVideo();
		void initBackgrounds();

		Screen* getScreen(ScreenId screenId);
		void clearScreen(ScreenId screenId);
		u16* getBuffer(ScreenId screenId);

		void swapBuffer(ScreenId screenId);

		void drawSprite(ScreenId screenId, bool dma, int16 x, int16 y, Sprite* sprite);
		void drawSprite(ScreenId screenId, bool dma, int16 x, int16 y, Sprite* sprite, SpriteRegion* region);

		void drawLineHorizontal(ScreenId screenId, int16 x, int16 y, u16 length, u16 color);
		void drawLineVertical(ScreenId screenId, int16 x, int16 y, u16 length, u16 color);
		void drawPixel(ScreenId screenId, int16 x, int16 y, u16 pixel);

		void drawString(ScreenId screenId, const char* string, u16 x, u16 y, u16 width, u16 height);

		void fillBackground(ScreenId screenId, u16 color);
	};
}

#endif /* VIDEO_H_ */
