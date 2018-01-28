/*
 * SpriteRegion.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "SpriteRegion.h"

namespace KIWF {

	SpriteRegion::SpriteRegion(u16 x, u16 y, u16 width, u16 height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	SpriteRegion::~SpriteRegion() {}

	u16 SpriteRegion::getX() {
		return this->x;
	}

	u16 SpriteRegion::getY() {
		return this->y;
	}

	u16 SpriteRegion::getWidth() {
		return this->width;
	}

	u16 SpriteRegion::getHeight() {
		return this->height;
	}

	void SpriteRegion::setX(u16 x) {
		this->x = x;
	}
	void SpriteRegion::setY(u16 y) {
		this->y = y;
	}
}
