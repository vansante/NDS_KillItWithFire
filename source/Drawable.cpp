/*
 * Drawable.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "Drawable.h"

namespace KIWF {

	Drawable::Drawable() {}

	Drawable::~Drawable() {}

	u16 Drawable::getX() {
		return this->x;
	}

	u16 Drawable::getY() {
		return this->y;
	}

	u16 Drawable::getWidth() {
		return this->sprite->getTileWidth();
	}

	u16 Drawable::getHeight() {
		return this->sprite->getTileHeight();
	}

	DrawPriority Drawable::getDrawPriority() {
		return this->drawPriority;
	}

	Sprite* Drawable::getSprite() {
		return this->sprite;
	}
}
