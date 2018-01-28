/*
 * Mushroom.cpp
 *
 *  Created on: 4 jun. 2011
 *      Author: Paul
 */

#include "Mushroom.h"

namespace KIWF {

	Mushroom::Mushroom(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->health = MAX_HEALTH;
		this->activeRange = 350;
		this->allowCleanUp = false;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;

		this->sprite = SpriteManager::getInstance().get(MUSHROOM_SPRITE);
	}

	Mushroom::~Mushroom() {}

	void Mushroom::enterActiveList(){};

	void Mushroom::interact(Drawable* drawable) {
		drawable->upgrade();
		this->health = 0;
	}

	void Mushroom::destroy() {
		this->health = 0;
	}

	void Mushroom::bite(u16 damage) {}

	void Mushroom::burn(u16 damage) {
		this->health -= damage;
		if (this->health < 0) {
			this->health = 0;
		}
	}

	void Mushroom::upgrade() {}

	void Mushroom::fuel(u16 amount) {}

	void Mushroom::heal(u16 amount) {}

	void Mushroom::cake() {}

	void Mushroom::doAction() {
		if (this->health <= 0) {
			this->level->destroyObject(this);
			return;
		}
	}
	void Mushroom::draw(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
}
