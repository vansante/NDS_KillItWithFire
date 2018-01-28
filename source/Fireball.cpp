/*
 * Fireball.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */
#include "Fireball.h"
#include "Video.h"
#include "SpriteManager.h"
#include "SpriteRegion.h"

namespace KIWF {

	Fireball::Fireball(u16 x, u16 y, Direction direction, bool upgraded = false) {
		this->x = x;
		this->y = y;
		this->direction = direction;
		this->energy = START_ENERGY;
		this->allowCleanUp = true;
		this->impassable = false;

		if (upgraded) {
			this->state = STATE_SUPER_FLYING;
			this->energy += 400;
			this->drawPriority = PRIORITY_1;
			this->activeRange = 500;
		} else {
			this->state = STATE_FLYING;
			this->drawPriority = PRIORITY_3;
			this->activeRange = 350;
		}

		this->sprite = SpriteManager::getInstance().get(FIREBALL_FLY_SPRITE);

		if (spriteRegions[0] == NULL) {
			spriteRegions[0] = new SpriteRegion(0, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[1] = new SpriteRegion(20, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[2] = new SpriteRegion(40, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[3] = new SpriteRegion(60, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());

			// Destroy sprites
			spriteRegions[4] = new SpriteRegion(80, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[5] = new SpriteRegion(100, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());

			spriteRegions[6] = new SpriteRegion(0, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[7] = new SpriteRegion(20, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[8] = new SpriteRegion(40, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[9] = new SpriteRegion(60, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());

			spriteRegions[10] = new SpriteRegion(80, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			spriteRegions[11] = new SpriteRegion(100, 20, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		}
	}

	Fireball::~Fireball() {}

	void Fireball::enterActiveList(){};

	void Fireball::interact(Drawable* drawable) {
		if (this->state == STATE_FLYING || this->state == STATE_SUPER_FLYING) {
			drawable->burn(this->energy * ENERGY_DAMAGE);
			if (this->state == STATE_FLYING){
				this->state = STATE_DYING_1;
			}
		}
	}

	void Fireball::destroy() {
		this->energy = 0;
	}

	void Fireball::bite(u16 damage) {}

	void Fireball::burn(u16 damage) {}

	void Fireball::upgrade() {
		this->state = STATE_SUPER_FLYING;
		this->energy += 400;
	}

	void Fireball::fuel(u16 amount) {}

	void Fireball::heal(u16 amount) {}

	void Fireball::cake() {}

	void Fireball::doAction() {
		switch (this->state) {
		case STATE_FLYING:
		case STATE_SUPER_FLYING:
			this->energy--;
			if (this->energy <= 0) {
				this->state = STATE_DYING_1;
				return;
			}
			break;
		case STATE_DYING_1:
		case STATE_DYING_2:
		case STATE_SUPER_DYING_1:
		case STATE_SUPER_DYING_2:
			return;
		case STATE_DYING_3:
		case STATE_SUPER_DYING_3:
			this->level->destroyObject(this);
			return;
		}

		u16 nextX = this->x;
		u16 nextY = this->y;
		switch (this->direction) {
		case DIRECTION_UP:
			if (this->state == STATE_SUPER_FLYING) {
				nextY -= SPEED * 2;
			} else {
				nextY -= SPEED;
			}
			break;
		case DIRECTION_DOWN:
			if (this->state == STATE_SUPER_FLYING) {
				nextY += SPEED * 2;
			} else {
				nextY += SPEED;
			}
			break;
		case DIRECTION_LEFT:
		case DIRECTION_UP_LEFT:
		case DIRECTION_DOWN_LEFT:
			if (this->state == STATE_SUPER_FLYING) {
				nextX -= SPEED * 2;
			} else {
				nextX -= SPEED;
			}
			break;
		case DIRECTION_RIGHT:
		case DIRECTION_UP_RIGHT:
		case DIRECTION_DOWN_RIGHT:
			if (this->state == STATE_SUPER_FLYING) {
				nextX += SPEED * 2;
			} else {
				nextX += SPEED;
			}
			break;
		}
		u8 type = this->level->detectLevelCollision(nextX, nextY, this->sprite->getTileWidth(), this->sprite->getTileHeight());

		if (type == COLLIDE_NONE || type == COLLIDE_OBJECT) {
			this->x = nextX;
			this->y = nextY;
		} else {
			this->state = STATE_DYING_1;
		}
	}

	void Fireball::draw(Video* video) {
		switch (this->state) {
		case STATE_FLYING:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[this->direction]);
			break;
		case STATE_DYING_1:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[4]);
			this->state = STATE_DYING_2;
			break;
		case STATE_DYING_2:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[5]);
			this->state = STATE_DYING_3;
			break;
		case STATE_SUPER_FLYING:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[6 + this->direction]);
			break;
		case STATE_SUPER_DYING_1:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[10]);
			this->state = STATE_SUPER_DYING_2;
			break;
		case STATE_SUPER_DYING_2:
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, spriteRegions[11]);
			this->state = STATE_SUPER_DYING_3;
			break;
		default:
			break;
		}
	}

	SpriteRegion* Fireball::spriteRegions[Fireball::NUM_SPRITE_REGIONS];
}
