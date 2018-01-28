/*
 * BurnableBlock.cpp
 *
 *  Created on: Jun 11, 2011
 *      Author: aeterno
 */

#include "BurnableBlock.h"

namespace KIWF {

	BurnableBlock::BurnableBlock(u16 x, u16 y){
		this->x = x;
		this->y = y;
		this->sprite = SpriteManager::getInstance().get(CRATE_SPRITE);
		this->impassable = true;
		this->state = BLOCK_NORMAL;
		this->activeRange = 400;
		this->allowCleanUp = false;
		this->health = MAX_HEALTH;
		this->drawPriority = PRIORITY_4;

		if (this->spriteRegions[0] == NULL ) {
			this->spriteRegions[0] = new SpriteRegion(0, 0, 16, 16);
			this->spriteRegions[1] = new SpriteRegion(16, 0, 16, 16);
			this->spriteRegions[2] = new SpriteRegion(32, 0, 16, 16);
		}
	}

	BurnableBlock::~BurnableBlock(){}

	void BurnableBlock::enterActiveList(){};

	void BurnableBlock::interact(Drawable* drawable){

	}

	void BurnableBlock::destroy(){
		this->health = 0;
	}

	void BurnableBlock::bite(u16 damage){}

	void BurnableBlock::burn(u16 damage){
		if (this->state != BLOCK_BURNING) {
			this->sprite = SpriteManager::getInstance().get(CRATE_BURNING_SPRITE);
			this->animationFrame = 0;
			this->state = BLOCK_BURNING;
		}
	}

	void BurnableBlock::upgrade() {}

	void BurnableBlock::fuel(u16 amount){}

	void BurnableBlock::heal(u16 amount){}

	void BurnableBlock::cake() {}

	void BurnableBlock::doAction(){
		if (this->state == BLOCK_BURNING) {
			this->animationFrame++;

			if (this->animationFrame >= 20) {
				this->level->destroyObject(this);
				return;
			}
		}
	}

	void BurnableBlock::draw(Video* video){
		if (this->state == BLOCK_NORMAL) {
			video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
		} else if (this->state == BLOCK_BURNING) {
			u8 frame = this->animationFrame / 7;
			if (frame <= 2) {
				video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, this->spriteRegions[frame]);
			}
		}
	}

	SpriteRegion* BurnableBlock::spriteRegions[BurnableBlock::NUM_SPRITE_REGIONS];
}
