/*
 * FuelBarrel.cpp
 *
 *  Created on: 5 jun. 2011
 *      Author: Paul
 */

#include "FuelBarrel.h"

namespace KIWF {

	FuelBarrel::FuelBarrel(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->activeRange = 350;
		this->health = MAX_HEALTH;
		this->allowCleanUp = false;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;

		this->sprite = SpriteManager::getInstance().get(FUEL_BARREL_SPRITE);
	}

	FuelBarrel::~FuelBarrel() {}

	void FuelBarrel::enterActiveList(){};

	void FuelBarrel::interact(Drawable* drawable) {
		drawable->fuel(FUEL_AMOUNT);
		this->health = 0;
	}

	void FuelBarrel::destroy() {
		this->health = 0;
	}

	void FuelBarrel::bite(u16 damage) {}

	void FuelBarrel::burn(u16 damage) {
		this->health -= damage;
		if (this->health < 0) {
			this->health = 0;
		}
	}

	void FuelBarrel::upgrade() {}

	void FuelBarrel::fuel(u16 amount) {}

	void FuelBarrel::heal(u16 amount) {
		this->health += amount;
		if (this->health > MAX_HEALTH) {
			this->health = MAX_HEALTH;
		}
	}

	void FuelBarrel::cake() {}

	void FuelBarrel::doAction() {
		if (this->health <= 0) {
			this->level->destroyObject(this);
			return;
		}
	}
	void FuelBarrel::draw(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
}
