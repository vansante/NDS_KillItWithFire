/*
 * Firestream.cpp
 *
 *  Created on: 4 jun. 2011
 *      Author: Paul
 */

#include "Firestream.h"

namespace KIWF {

	Firestream::Firestream(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->energy = START_ENERGY;
		this->activeRange = 200;
		this->allowCleanUp = true;
		this->drawPriority = PRIORITY_3;
		this->impassable = false;

		this->sprite = SpriteManager::getInstance().get(FIRESTREAM_SPRITE);
	}

	Firestream::~Firestream() {}

	void Firestream::enterActiveList(){};

	void Firestream::interact(Drawable* drawable) {
		drawable->burn(this->energy);
		this->energy = 0;
	}

	void Firestream::destroy() {
		this->energy = 0;
	}

	void Firestream::bite(u16 damage) {}

	void Firestream::burn(u16 damage) {}

	void Firestream::upgrade() {}

	void Firestream::fuel(u16 amount) {}

	void Firestream::heal(u16 amount) {}

	void Firestream::cake() {}

	void Firestream::doAction() {
		this->energy--;
		if (this->energy <= 0) {
			this->level->destroyObject(this);
			return;
		}
		u16 nextY = this->y += SPEED;
		u8 type = this->level->detectLevelCollision(this->x, nextY, this->sprite->getWidth(), this->sprite->getHeight());

		if (type == COLLIDE_NONE) {
			this->y = nextY;
		} else {
			this->level->destroyObject(this);
			return;
		}
	}

	void Firestream::draw(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
}
