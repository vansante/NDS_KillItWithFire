/*
 * Hamburger.cpp
 *
 *  Created on: 5 jun. 2011
 *      Author: Paul
 */

#include "Hamburger.h"

namespace KIWF {

	Hamburger::Hamburger(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->health = MAX_HEALTH;
		this->activeRange = 350;
		this->allowCleanUp = false;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;

		this->sprite = SpriteManager::getInstance().get(HAMBURGER_SPRITE);
	}

	Hamburger::~Hamburger() {}

	void Hamburger::enterActiveList(){};

	void Hamburger::interact(Drawable* drawable) {
		drawable->heal(RESTORED_HEALTH_AMOUNT);
		this->health = 0;
	}

	void Hamburger::destroy() {
		this->health = 0;
	}

	void Hamburger::bite(u16 damage) {}

	void Hamburger::burn(u16 damage) {
		this->health -= damage;
		if (this->health < 0) {
			this->health = 0;
		}
	}

	void Hamburger::upgrade() {}

	void Hamburger::fuel(u16 amount) {}

	void Hamburger::heal(u16 amount) {}

	void Hamburger::cake() {}

	void Hamburger::doAction() {
		if (this->health <= 0) {
			this->level->destroyObject(this);
			return;
		}
	}
	void Hamburger::draw(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
}
