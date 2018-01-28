/*
 * Screen.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "Screen.h"

namespace KIWF {

	Screen::Screen(u16* framebuffer, bool autoClear, bool autoSwap) {
		this->framebuffer = framebuffer;
		this->buffer = (u16*) malloc(BUFFER_BYTE_SIZE);
		this->autoClear = autoClear;
		this->autoSwap = autoSwap;

		this->bufferStartX = 0;
		this->bufferStartY = 0;
	}

	Screen::~Screen() {
		free(this->buffer);
	}

	void Screen::setAutoClear(bool autoClear) {
		this->autoClear = autoClear;
	}

	void Screen::setAutoSwap(bool autoSwap) {
		this->autoSwap = autoSwap;
	}

	bool Screen::getAutoSwap() {
		return this->autoSwap;
	}

	void Screen::setBufferOrigin(u16 bufferStartX, u16 bufferStartY) {
		this->bufferStartX = bufferStartX;
		if (this->bufferStartX < 0 || this->bufferStartX > Screen::WIDTH) {
			this->bufferStartX = 0;
		}
		this->bufferStartY = bufferStartY;
		if (this->bufferStartY < 0 || this->bufferStartY > Screen::HEIGHT) {
			this->bufferStartY = 0;
		}
	}

	u16* Screen::getBuffer() {
		return this->buffer;
	}

	void Screen::swapBuffer() {
		if (this->bufferStartX == 0 && this->bufferStartY == 0) {
			dmaCopyHalfWords(DMA_CHANNEL, this->buffer, this->framebuffer, BUFFER_BYTE_SIZE);
		} else {
			u16 actualBufferY;
			u16 width;
			u16 framebufferY = 0;

			for (u16 bufferY = this->bufferStartY; bufferY < this->bufferStartY + HEIGHT; bufferY++) {
				actualBufferY = bufferY % HEIGHT;
				width = WIDTH - this->bufferStartX;

				dmaCopyHalfWords(
					DMA_CHANNEL,
					& this->buffer[actualBufferY * WIDTH + this->bufferStartX],
					& this->framebuffer[framebufferY * WIDTH],
					width * sizeof(u16)
				);

				if (this->bufferStartX > 0) {
					dmaCopyHalfWords(
						DMA_CHANNEL,
						& this->buffer[actualBufferY * WIDTH],
						& this->framebuffer[framebufferY * WIDTH + width],
						(WIDTH - width) * sizeof(u16)
					);
				}

				framebufferY++;
			}
		}

		if (this->autoClear) {
			this->clearScreen();
		}
	}

	void Screen::clearScreen() {
		dmaFillWords(0, this->buffer, BUFFER_BYTE_SIZE);
	}
}
