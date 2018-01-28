/*
 * Tombstone.cpp
 *
 *  Created on: Jun 4, 2011
 *      Author: aeterno
 */
#include "Tombstone.h"

namespace KIWF {

	Tombstone::Tombstone(u16 x, u16 y, Level* level, TombstoneState state){
		this->x = x;
		this->y = y;
		this->level = level;
		this->counter = FRAMES_PER_SPAWN;
		this->animationFrame = 0;
		this->activeRange = 350;
		this->allowCleanUp = false;
		this->state = state;
		this->health = 600;
		this->impassable = false;
		this->drawPriority = PRIORITY_4;

		this->sprite = SpriteManager::getInstance().get(TOMBSTONE_SPRITE);

		if (this->spriteRegions[0] == NULL) {
			//	Wood tombstone
			this->spriteRegions[0] = new SpriteRegion(0, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			//	Stone tombstone
			this->spriteRegions[1] = new SpriteRegion(24, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			//	Golden tombstone
			this->spriteRegions[2] = new SpriteRegion(48, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());

			//	Wooden burning
			this->spriteRegions[3] = new SpriteRegion(0, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[4] = new SpriteRegion(24, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[5] = new SpriteRegion(48, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[6] = new SpriteRegion(72, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());

			//	Wooden Death
			this->spriteRegions[7] = new SpriteRegion(0, 64, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[8] = new SpriteRegion(24, 64, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[9] = new SpriteRegion(48, 64, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			this->spriteRegions[10] = new SpriteRegion(72, 64, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		}
	}

	Tombstone::~Tombstone() {}

	void Tombstone::enterActiveList() {
		this->counter = FRAMES_PER_SPAWN;
	}

	void Tombstone::interact(Drawable* drawable){}

	void Tombstone::destroy(){}

	void Tombstone::bite(u16 damage){}

	void Tombstone::burn(u16 damage) {
		if (this->state == STATE_WOOD || this->state == STATE_WOOD_BURNING) {
			this->state = STATE_WOOD_BURNING;
			this->reduceHealth(damage);
		}
	}

	void Tombstone::upgrade(){}

	void Tombstone::fuel(u16 amount){}

	void Tombstone::heal(u16 amount) {}

	void Tombstone::cake() {}

	void Tombstone::reduceHealth(u8 amount) {
		this->health -= amount;
		if (this->health < 0) {
			this->health = 0;
		}
		if (this->health == 0 && this->state != STATE_WOOD_DYING) {
			this->state = STATE_WOOD_DYING;
			this->animationFrame = 0;
			SoundManager::getInstance().playSound(SFX_BURN);
		}
	}

	void Tombstone::doAction() {
		if (this->state == STATE_WOOD_BURNING || this->state == STATE_WOOD_DYING) {
			this->animationFrame++;
			this->animationFrame %= 100;
		}

		if (this->state == STATE_WOOD_DYING) {
			if (this->animationFrame >= 79) {
				this->level->destroyObject(this);
				return;
			}
		}

		if (this->state == STATE_WOOD_BURNING) {
			this->reduceHealth(1);
		}

		if (this->state != STATE_WOOD_DYING) {
			this->counter++;
			if (counter >= FRAMES_PER_SPAWN) {
				if (!this->level->objectCapacityMaxed()) {
					if (this->state == STATE_WOOD || this->state == STATE_STONE) {
						this->level->addObject(new Zombie(this->x, this->y, DIRECTION_LEFT, true, STATE_NORMAL));
						SoundManager::getInstance().playSound(SFX_ZOMBIE_MOAN);
					} else if (this->state == STATE_WOOD_BURNING) {
						this->level->addObject(new Zombie(this->x, this->y, DIRECTION_LEFT, true, STATE_BURNING));
						SoundManager::getInstance().playSound(SFX_ZOMBIE_MOAN);
					} else if (this->state == STATE_GOLDEN) {
						this->level->addObject(new Zombie(this->x, this->y - 25, DIRECTION_LEFT, true, STATE_SUPER_NORMAL));
						SoundManager::getInstance().playSound(SFX_SUPER_ZOMBIE_MOAN);
					}
				}
				this->counter = 0;
			}
		}
	}

	void Tombstone::draw(Video* video) {
		u8 frame = 0;
		switch (this->state) {
		case STATE_WOOD:
			frame = 0;
			break;
		case STATE_STONE:
			frame = 1;
			break;
		case STATE_GOLDEN:
			frame = 2;
			break;
		case STATE_WOOD_BURNING:
			frame = 4 + this->animationFrame / 25;
			break;
		case STATE_WOOD_DYING:
			frame = 7 + this->animationFrame / 25;
			break;
		}
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite,this->spriteRegions[frame]);
	}

	SpriteRegion* Tombstone::spriteRegions[Tombstone::NUM_SPRITE_REGIONS];
}
