/*
 * Video.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "Video.h"
#include "constants.h"

namespace KIWF {

	Video::Video() {
		this->initVideo();
		this->initBackgrounds();

		this->screens[MAIN_SCREEN_BACKGROUND] = new Screen(_MAIN_SCREEN_BACKGROUND, false, true);
		this->screens[MAIN_SCREEN_FOREGROUND] = new Screen(_MAIN_SCREEN_FOREGROUND, false, true);
		this->screens[TOUCH_SCREEN_FOREGROUND] = new Screen(_TOUCH_SCREEN_FOREGROUND, false, false);
	}

	Video::~Video() {}

	Screen* Video::getScreen(ScreenId screenId) {
		return this->screens[screenId];
	}

	void Video::clearScreen(ScreenId screenId) {
		return this->screens[screenId]->clearScreen();
	}

	u16* Video::getBuffer(ScreenId screenId) {
		return this->screens[screenId]->getBuffer();
	}

	void Video::swapBuffer(ScreenId screenId) {
		this->screens[screenId]->swapBuffer();
	}

	void Video::drawSprite(ScreenId screenId, bool dma, int16 x, int16 y, Sprite* sprite) {
		this->drawSprite(screenId, dma, x, y, sprite, NULL);
	}

	void Video::drawSprite(ScreenId screenId, bool dma, int16 x, int16 y, Sprite* sprite, SpriteRegion* region) {
		u16 spriteX, spriteY, spriteWidth, spriteHeight;

		// Get starting coordinates and dimensions
		if (region == NULL) {
			spriteX = 0;
			spriteY = 0;
			spriteWidth = sprite->getWidth();
			spriteHeight = sprite->getHeight();
		} else {
			spriteX = region->getX();
			spriteY = region->getY();
			spriteWidth = region->getWidth();
			spriteHeight = region->getHeight();
		}

		// Is this sprite even on the screen?
		if (x + spriteWidth < 0 || y + spriteHeight < 0 || x > Screen::WIDTH || y > Screen::HEIGHT) {
			return;
		}

		// Shave off parts offscreen (X)
		if (x < 0) {
			spriteWidth = x + spriteWidth;
			spriteX = spriteX + - x;
			x = 0;
		} else if (x + spriteWidth >= Screen::WIDTH) {
			spriteWidth = Screen::WIDTH - x;
		}
		if (spriteWidth <= 0) {
			// Not on the screen
			return;
		}

		// Shave off parts offscreen (Y)
		if (y < 0) {
			spriteHeight = y + spriteHeight;
			spriteY = spriteY + - y;
			y = 0;
		} else if (y + spriteHeight >= Screen::HEIGHT) {
			spriteHeight = Screen::HEIGHT - y;
		}
		if (spriteHeight <= 0) {
			// Not on the screen
			return;
		}

		u16* buffer = this->screens[screenId]->getBuffer();
		if (dma) {
			int16 screenY;

			for (screenY = y; screenY < y + spriteHeight; screenY++) {
				// Lets put the hardware to work
				dmaCopyHalfWords(
					DMA_CHANNEL,
					& sprite->getPixelData()[spriteY * sprite->getWidth() + spriteX],
					& buffer[screenY * Screen::WIDTH + x],
					spriteWidth * 2
				);
				spriteY++;
			}
		} else {
			int16 screenX, screenY;
			u16 curPixel;
			u16 startSpriteY = spriteY;

			for (screenX = x; screenX < x + spriteWidth; screenX++) {
				spriteY = startSpriteY;

				for (screenY = y; screenY < y + spriteHeight; screenY++) {
					curPixel = sprite->getPixelData()[spriteY * sprite->getWidth() + spriteX];
					// Only draw this pixel if it is actually visible
					if (curPixel & VISIBILITY_BIT) {
						buffer[screenY * Screen::WIDTH + screenX] = curPixel;
					}

					spriteY++;
				}
				spriteX++;
			}
		}
	}

	void Video::drawLineHorizontal(ScreenId screenId, int16 x, int16 y, u16 length, u16 color) {
		if (y < 0 || y > Screen::HEIGHT) {
			return;
		}
		if (x < 0) {
			length += x;
			x = 0;
		} else if (x + length >= Screen::WIDTH) {
			length = Screen::WIDTH - x;
		}
		if (length == 0) {
			// Not on the screen
			return;
		}
		dmaFillHalfWords(
			color,
			& this->screens[screenId]->getBuffer()[y * Screen::WIDTH + x],
			length * 2
		);
	}

	void Video::drawLineVertical(ScreenId screenId, int16 x, int16 y, u16 length, u16 color) {
		if (x < 0 || x > Screen::WIDTH) {
			return;
		}
		if (y < 0) {
			length += y;
			y = 0;
		} else if (y + length >= Screen::HEIGHT) {
			length = Screen::HEIGHT - y;
		}
		u16* buffer = this->screens[screenId]->getBuffer();

		for (u16 screenY = y ; screenY < y + length; screenY++) {
			buffer[screenY * Screen::WIDTH + x] = color;
		}
	}

	void Video::drawPixel(ScreenId screenId, int16 x, int16 y, u16 pixel) {
		if (x >= 0 && y >= 0 && x < Screen::WIDTH && y < Screen::HEIGHT) {
			this->screens[screenId]->getBuffer()[y * Screen::WIDTH + x] = pixel;
		}
	}

	void Video::drawString(ScreenId screenId, const char* string, u16 startX, u16 startY, u16 width, u16 height) {
		Sprite* sprite = SpriteManager::getInstance().get(FONT_SPRITE);

		u16 x = startX;
		u16 y = startY;
		SpriteRegion* region = new SpriteRegion(0, 0, sprite->getTileWidth(), sprite->getTileHeight());

		u16 i = 0;
		char curChar;
		while (string[i] != '\0') {
			curChar = string[i];

			if (curChar == 10) {
				// Newline char
				x = startX;
				y += sprite->getTileHeight();
				i++;
				continue;
			}
			if (x + sprite->getTileWidth() > startX + width) {
				// Horizontal space is exhausted, new line
				x = startX;
				y += sprite->getTileHeight();
			}
			if (y + sprite->getTileHeight() > startY + height) {
				// Our vertical space is exhausted, stop the presses!
				break;
			}

			// We only do the basic ACSII set and we make non printable chars a space
			if (curChar < 32 || curChar > 127) {
				curChar = 32;
			}
			// Space is our first char (position 0)
			curChar -= 32;

			region->setX((curChar % 16) * sprite->getTileWidth());
			region->setY((curChar / 16) * sprite->getTileHeight());
//			iprintf("%c %d -  %d, %d - %d, %d\n", curChar+32, curChar, x, y, region->getX(), region->getY());

			this->drawSprite(screenId, false, x, y, sprite, region);

			x += sprite->getTileWidth();

			i++;
		}
		delete region;
	}

	void Video::fillBackground(ScreenId screenId, u16 color) {
		dmaFillHalfWords(color, this->screens[screenId]->getBuffer(), Screen::BUFFER_BYTE_SIZE);
	}

	void Video::swapBuffers() {
		for (u8 i = 0; i < NUM_SCREENS; i++) {
			if (this->screens[i]->getAutoSwap()) {
				this->screens[i]->swapBuffer();
			}
		}
	}

	/*
	 * Initiates both screens en sets the video mode.
	 */
	void Video::initVideo() {
		// Set up main screen (mode 5 -> two bitmap layers)
		REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;

	#ifdef DEBUG_MODE
		consoleDemoInit();
		iprintf("Debug mode is on!\n");
	#else
		// Set up sub screen (mode 3 -> one bitmap layer)
		REG_DISPCNT_SUB = MODE_3_2D | DISPLAY_BG3_ACTIVE;
	#endif
		// Map memory banks to the screens
		VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
		VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG;
		VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	}

	/*
	 * Sets background modes and memory base.
	 */
	void Video::initBackgrounds() {
		// Main screen second background (16 bit bitmap -> 256x256 pixels)
		REG_BG2CNT = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(1);
		// No scaling, rotation and offset
		REG_BG2PA = (1 << 8);
		REG_BG2PB = 0;
		REG_BG2PC = 0;
		REG_BG2PD = (1 << 8);
		REG_BG2X = 0;
		REG_BG2Y = 0;

		// Main screen third background (16 bit bitmap -> 256x256 pixels)
		REG_BG3CNT = BG_BMP16_256x256 | BG_BMP_BASE(6) | BG_PRIORITY(0);
		// No scaling, rotation and offset
		REG_BG3PA = (1 << 8);
		REG_BG3PB = 0;
		REG_BG3PC = 0;
		REG_BG3PD = (1 << 8);
		REG_BG3X = 0;
		REG_BG3Y = 0;

		#ifndef DEBUG_MODE
		// Sub screen second background (16 bit bitmap -> 256x256 pixels)
		REG_BG3CNT_SUB = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(0);
		// No scaling, rotation and offset
		REG_BG3PA_SUB = (1 << 8);
		REG_BG3PB_SUB = 0;
		REG_BG3PC_SUB = 0;
		REG_BG3PD_SUB = (1 << 8);
		REG_BG3X_SUB = 0;
		REG_BG3Y_SUB = 0;
		#endif
	}
}
