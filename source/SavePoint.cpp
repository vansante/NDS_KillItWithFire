/*
 * SavePoint.cpp
 *
 *  Created on: 13 jun. 2011
 *      Author: Paul
 */

#include "SavePoint.h"

namespace KIWF {

	SavePoint::SavePoint(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->activeRange = 350;
		this->allowCleanUp = false;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;
		this->isSaved = false;

		this->sprite = SpriteManager::getInstance().get(SAVE_POINT_SPRITE);

		if (this->spriteRegions[0] == NULL) {
			this->spriteRegions[0] = new SpriteRegion(0, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[1] = new SpriteRegion(20, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		}
	}

	SavePoint::~SavePoint() {}

	void SavePoint::enterActiveList(){};

	void SavePoint::interact(Drawable* drawable) {}

	void SavePoint::destroy() {}

	void SavePoint::bite(u16 damage) {}

	void SavePoint::burn(u16 damage) {}

	void SavePoint::upgrade() {}

	void SavePoint::fuel(u16 amount) {}

	void SavePoint::heal(u16 amount) {}

	void SavePoint::cake() {}

	void SavePoint::doAction() {
		if (!this->isSaved) {
			u16 playerX = this->level->getPlayer()->getCenterX();
			u16 playerY = this->level->getPlayer()->getCenterY();

			if (playerX >= this->x && playerX <= this->x + this->getWidth() && playerY >= this->y && playerY <= this->y + this->getHeight()) {
				this->level->setPlayerSpawn(this->x, this->y);
				this->isSaved = true;
			}
		}
	}

	void SavePoint::draw(Video* video) {
		if (this->isSaved) {
			video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, this->spriteRegions[1]);
		}  else {
			video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, this->spriteRegions[0]);
		}
	}

	SpriteRegion* SavePoint::spriteRegions[SavePoint::SAVE_POINT_NUM_SPRITE_REGIONS];
}
