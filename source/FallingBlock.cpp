/*
 * FallingBlock.cpp
 *
 *  Created on: Jun 12, 2011
 *      Author: aeterno
 */

#include "FallingBlock.h"

namespace KIWF{

	FallingBlock::FallingBlock(u16 x, u16 y){
		this->x = x;
		this->y = y;
		this->activeRange = 400;
		this->impassable = true;
		this->state = FBLOCK_STATE_STATIC;
		this->drawPriority = PRIORITY_4;
		this->fallCounter = 16;
		this->allowCleanUp = false;
		this->ySpeed = 1;

		this->sprite = SpriteManager::getInstance().get(FALLING_BLOCK_SPRITE);
	}

	FallingBlock::~FallingBlock() {}

	void FallingBlock::enterActiveList(){};
	void FallingBlock::interact(Drawable* drawable) {}
	void FallingBlock::destroy() {}
	void FallingBlock::bite(u16 damage) {}
	void FallingBlock::burn(u16 damage) {}
	void FallingBlock::upgrade() {}
	void FallingBlock::fuel(u16 amount) {}
	void FallingBlock::heal(u16 amount) {}
	void FallingBlock::cake() {}

	void FallingBlock::applySpeeds() {
		u8 type;
		type = this->level->detectLevelCollision(
			this->x, this->y + this->ySpeed,
			this->sprite->getTileWidth(), this->sprite->getTileHeight()
		);

		if (!(type & COLLIDE_EDGE) && !(type & COLLIDE_TERRAIN)) {
			this->y += this->ySpeed;
		} else {
			this->ySpeed--;
		}
	}

	void FallingBlock::doAction(){
		if (this->state == FBLOCK_STATE_FALLING && this->ySpeed == 0) {
			this->level->destroyObject(this);
			return;
		}
		if (this->state == FBLOCK_STATE_STATIC) {
			u16 playerX = this->level->getPlayer()->getX();
			u16 playerY = this->level->getPlayer()->getY();
			u8 width = this->level->getPlayer()->getWidth();
			u8 height = this->level->getPlayer()->getHeight();

			if (this->fallCounter > 0 && playerX + width >= this->x && playerX <= this->x + this->getWidth() && playerY + height - 1 == this->y) {
				this->fallCounter--;
			} else if (this->fallCounter == 0) {
				this->state = FBLOCK_STATE_FALLING;
			}
		} else if (this->state == FBLOCK_STATE_FALLING) {
			this->fallCounter++;
			if (this->fallCounter % 5 == 0) {
				this->ySpeed++;
				if (this->ySpeed > 10) {
					this->ySpeed = 10;
				}
			}

			this->applySpeeds();
		}
	}

	void FallingBlock::draw(Video* video){
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
}
