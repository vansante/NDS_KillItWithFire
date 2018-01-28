/*
 * Sprite.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "Sprite.h"

namespace KIWF {

	Sprite::Sprite(u16 width, u16 height, u16* pixelData) {
		this->width = width;
		this->height = height;
		this->pixelData = pixelData;

		this->tileHeight = width;
		this->tileWidth = height;
	}

	Sprite::Sprite(u16 width, u16 height, u16 tileWidth, u16 tileHeight, u16* pixelData){
		this->width = width;
		this->height = height;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->pixelData = pixelData;
	}

	Sprite::~Sprite() {
		free(this->pixelData);
	}

	u16 Sprite::getWidth() {
		return this->width;
	}
	u16 Sprite::getHeight() {
		return this->height;
	}
	u16 Sprite::getTileWidth(){
		return this->tileWidth;
	}
	u16 Sprite::getTileHeight(){
		return this->tileHeight;
	}
	u16* Sprite::getPixelData() {
		return this->pixelData;
	}
	u16 Sprite::getPixelCount() {
		return this->width * this->height;
	}
	u16 Sprite::getByteSize() {
		return this->getPixelCount() * 2;
	}
}
