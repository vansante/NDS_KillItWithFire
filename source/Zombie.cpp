/*
 * Zombie.cpp
 *
 *  Created on: Jun 4, 2011
 *      Author: aeterno
 */

#include "Zombie.h"
#include "SpriteManager.h"
#include "SpriteRegion.h"

namespace KIWF{

	Zombie::Zombie(u16 x, u16 y, Direction direction, bool allowCleanUp, ZombieState state) {
		this->x = x;
		this->y = y;
		this->xSpeed = 0;
		this->ySpeed = 0;
		this->impassable = false;
		this->animationFrame = 0;
		this->direction = direction;
		this->activeRange = 350;
		this->allowCleanUp = allowCleanUp;
		this->drawPriority = PRIORITY_1;

		this->stalkerLevel = 20 + (rand() % 100);

		this->state = state;

		if (this->state == STATE_NORMAL) {
			this->sprite = SpriteManager::getInstance().get(ZOMBIE_SPRITE);
			this->health = MAX_HEALTH;
			this->speed = 1;
		} else if (this->state == STATE_BURNING) {
			this->sprite = SpriteManager::getInstance().get(BURNING_ZOMBIE_SPRITE);
			this->health = MAX_HEALTH;
			this->speed = 1;
		} else if (this->state == STATE_SUPER_NORMAL) {
			this->sprite = SpriteManager::getInstance().get(SUPER_ZOMBIE_SPRITE);
			this->health = SUPER_MAX_HEALTH;
			this->speed = 2;
		}

		if (this->spriteRegions[0] == NULL) {
			//	Left
			this->spriteRegions[0] = new SpriteRegion(0, 0, 20, 32);
			this->spriteRegions[1] = new SpriteRegion(20, 0, 20, 32);
			this->spriteRegions[2] = new SpriteRegion(40, 0, 20, 32);

			//	Right
			this->spriteRegions[3] = new SpriteRegion(0, 32, 20, 32);
			this->spriteRegions[4] = new SpriteRegion(20, 32, 20, 32);
			this->spriteRegions[5] = new SpriteRegion(40, 32, 20, 32);

			// Burning left
			this->spriteRegions[6] = new SpriteRegion(0, 0, 24, 35);
			this->spriteRegions[7] = new SpriteRegion(24, 0, 24, 35);
			this->spriteRegions[8] = new SpriteRegion(48, 0, 24, 35);
			// Burning right
			this->spriteRegions[9] = new SpriteRegion(0, 35, 24, 35);
			this->spriteRegions[10] = new SpriteRegion(24, 35, 24, 35);
			this->spriteRegions[11] = new SpriteRegion(48, 35, 24, 35);

			//	Burning to death
			this->spriteRegions[12] = new SpriteRegion(0, 0, 20, 35);
			this->spriteRegions[13] = new SpriteRegion(20, 0, 20, 35);
			this->spriteRegions[14] = new SpriteRegion(40, 0, 20, 35);
			this->spriteRegions[15] = new SpriteRegion(0, 35, 20, 35);
			this->spriteRegions[16] = new SpriteRegion(20, 35, 20, 35);
			this->spriteRegions[17] = new SpriteRegion(40, 35, 20, 35);

			this->spriteRegions[18] = new SpriteRegion(0, 0, 32, 56);
			this->spriteRegions[19] = new SpriteRegion(32, 0, 32, 56);
			this->spriteRegions[20] = new SpriteRegion(64, 0, 32, 56);

			this->spriteRegions[21] = new SpriteRegion(0, 56, 32, 56);
			this->spriteRegions[22] = new SpriteRegion(32, 56, 32, 56);
			this->spriteRegions[23] = new SpriteRegion(64, 56, 32, 56);
		}
	}

	Zombie::~Zombie() {}

	void Zombie::interact(Drawable* drawable) {
		if (this->state != STATE_DYING && this->state != STATE_SUPER_DYING) {
			drawable->bite(ZOMBIE_DAMAGE);
		}
	}

	void Zombie::destroy() {
		this->health = 0;
	}

	void Zombie::bite(u16 damage) {}

	void Zombie::burn(u16 damage) {
		if (this->state == STATE_NORMAL) {
			this->state = STATE_BURNING;
			this->sprite = SpriteManager::getInstance().get(BURNING_ZOMBIE_SPRITE);
		} else if (this->state == STATE_SUPER_NORMAL) {
			this->state = STATE_SUPER_BURNING;
			this->sprite = SpriteManager::getInstance().get(SUPER_ZOMBIE_BURNING_SPRITE);
		}
		this->reduceHealth(damage);
	}

	void Zombie::upgrade() {
		if (this->state == STATE_NORMAL) {
			this->y -= 25;
			this->state = STATE_SUPER_NORMAL;
			this->sprite = SpriteManager::getInstance().get(SUPER_ZOMBIE_SPRITE);
			this->health += (SUPER_MAX_HEALTH - MAX_HEALTH);
			this->speed = 2;
		} else if (this->state == STATE_BURNING) {
			this->y -= 25;
			this->state = STATE_SUPER_BURNING;
			this->sprite = SpriteManager::getInstance().get(SUPER_ZOMBIE_BURNING_SPRITE);
			this->health += (SUPER_MAX_HEALTH - MAX_HEALTH);
			this->speed = 2;
		} else if (this->state == STATE_SUPER_BURNING || this->state == STATE_SUPER_NORMAL) {
			this->health = SUPER_MAX_HEALTH;
		}
		SoundManager::getInstance().playSound(SFX_SUPER_ZOMBIE_MOAN);
	}

	void Zombie::enterActiveList() {}

	void Zombie::fuel(u16 amount) {}

	void Zombie::heal(u16 amount) {}

	void Zombie::cake() {}

	void Zombie::reduceHealth(u8 amount) {
		this->health -= amount;
		if (this->health < 0) {
			this->health = 0;
		}
		if (this->health == 0 && this->state != STATE_DYING && this->state != STATE_SUPER_DYING) {
			if (this->state == STATE_SUPER_BURNING) {
				this->state = STATE_SUPER_DYING;
				this->sprite = SpriteManager::getInstance().get(SUPER_ZOMBIE_DEATH_SPRITE);
			} else if (this->state == STATE_BURNING){
				this->state = STATE_DYING;
				this->sprite = SpriteManager::getInstance().get(DEATH_ZOMBIE_SPRITE);
			}
			this->animationFrame = 0;
			SoundManager::getInstance().playSound(SFX_BURN);
		}
	}

	void Zombie::reverseDirection(){
		if (this->direction == DIRECTION_LEFT) {
			this->direction = DIRECTION_RIGHT;
		} else if (this->direction == DIRECTION_RIGHT) {
			this->direction = DIRECTION_LEFT;
		}
	}

	void Zombie::applyGravity(){
		u8 type = 0;
		if(this->state != STATE_SUPER_NORMAL && this->state != STATE_SUPER_BURNING) {
			type = this->level->detectLevelCollision(this->x, this->y + 1, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
		} else {
			type = this->level->detectLevelCollision(this->x, this->y + 1, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		}

		if (type == COLLIDE_NONE || (type & COLLIDE_LAVA && !(type & COLLIDE_TERRAIN))) {
			this->ySpeed++;
			if (this->ySpeed > 10) {
				this->ySpeed = 10;
			}
		}
	}

	void Zombie::jump() {
		this->ySpeed = -1;
		this->xSpeed = 0;
	}

	void Zombie::doAction(){
		if (this->state == STATE_NORMAL || this->state == STATE_BURNING || this->state == STATE_SUPER_NORMAL || this->state == STATE_SUPER_BURNING) {
			//	Dead zombies do not move, duh.

			//	Increment animation
			this->animationFrame++;
			this->animationFrame %= 46;

			if ((this->state == STATE_BURNING || this->state == STATE_SUPER_BURNING ) && this->animationFrame % 4 == 0) {
				this->reduceHealth(BURN_DAMAGE);
			}

			this->applyGravity();

			u16 playerX = this->level->getPlayer()->getX();

			if (playerX < this->x - this->stalkerLevel) {
				this->direction = DIRECTION_LEFT;
			} else if (playerX > this->x + this->stalkerLevel) {
				this->direction = DIRECTION_RIGHT;
			}

			if (this->direction == DIRECTION_LEFT) {
				this->xSpeed = -this->speed;
			} else {
				this->xSpeed = this->speed;
			}

			u16 nextX = this->x + this->xSpeed;
			u16 nextY = this->y + this->ySpeed;

			u8 type = 0 ;

			if (this->state != STATE_SUPER_NORMAL && this->state != STATE_SUPER_BURNING) {
				type = this->level->detectLevelCollision(nextX, nextY, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
			} else {
				type = this->level->detectLevelCollision(nextX, nextY, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			}

			if (type & COLLIDE_TERRAIN && ySpeed < 1) {
				if (this->state != STATE_DYING || this->state == STATE_SUPER_DYING) {
					this->jump();
				}
				nextX = this->x + this->xSpeed;
				nextY = this->y + this->ySpeed;
			} else if (ySpeed > 0) {
				this->xSpeed = 0;
				nextX = this->x + this->xSpeed;
				nextY = this->y + this->ySpeed;
			}

			if (this->state != STATE_SUPER_NORMAL && this->state != STATE_SUPER_BURNING){
				type = this->level->detectLevelCollision(nextX, nextY, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
			} else {
				type = this->level->detectLevelCollision(nextX, nextY, this->sprite->getTileWidth(), this->sprite->getTileHeight());
			}

			if (type == COLLIDE_NONE) {
				this->x = nextX;
				this->y = nextY;
			} else if (type & COLLIDE_LAVA && !(type & COLLIDE_TERRAIN)) {
				this->x = nextX;
				this->y = nextY;
				this->burn(LAVA_MELT_DAMAGE);
			} else if (type & COLLIDE_SPIKES && !(type & COLLIDE_TERRAIN)) {
				this->x = nextX;
				this->ySpeed = 0;
			} else {
				if (this->state != STATE_SUPER_NORMAL && this->state != STATE_SUPER_BURNING) {
					type = this->level->detectLevelCollision(this->x + this->xSpeed, this->y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
				} else {
					type = this->level->detectLevelCollision(this->x + this->xSpeed, this->y, this->sprite->getTileWidth(), this->sprite->getTileHeight());
				}

				if (type == COLLIDE_NONE) {
					this->ySpeed = 0;
				} else {
					if (this->state != STATE_SUPER_NORMAL && this->state != STATE_SUPER_BURNING) {
						type = this->level->detectLevelCollision(this->x, this->y + ySpeed, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
					} else {
						type = this->level->detectLevelCollision(this->x, this->y + ySpeed, this->sprite->getTileWidth(), this->sprite->getTileHeight());
					}

					if (type == COLLIDE_NONE) {
						this->xSpeed = 0;
					} else {
						this->xSpeed = 0;
						this->ySpeed = 0;
					}
				}
			}
		} else if (this->state == STATE_DYING || this->state == STATE_SUPER_DYING) {
			this->animationFrame++;

			if (this->animationFrame > 100) {
				this->level->destroyObject(this);
				return;
			}
		}
	}

	void Zombie::draw(Video* video) {
		u8 frame = 0;
		if (this->state == STATE_NORMAL) {
			frame = this->direction * 3 + this->animationFrame / 16;
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite, this->spriteRegions[frame]);
		} else if(this->state == STATE_BURNING) {
			frame = 6 + this->direction * 3 + this->animationFrame / 16;
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y) - 2, this->sprite, this->spriteRegions[frame]);
		} else if (this->state == STATE_DYING) {
			if (this->animationFrame < 20) {
				frame = 12;
			} else if (this->animationFrame < 40) {
				frame = 13;
			} else if (this->animationFrame < 60) {
				frame = 14;
			} else if (this->animationFrame < 80) {
				frame = 15;
			} else if (this->animationFrame < 100) {
				frame = 16;
			} else {
				frame = 17;
			}
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y) - 2, this->sprite, this->spriteRegions[frame]);
		} else if (this->state == STATE_SUPER_NORMAL || this->state == STATE_SUPER_BURNING){
			frame = 18 + this->direction * 3 + this->animationFrame / 16;
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y) - 2, this->sprite, this->spriteRegions[frame]);
		} else if (this->state == STATE_SUPER_DYING) {
			if (this->animationFrame < 20) {
				frame = 18;
			} else if (this->animationFrame < 40) {
				frame = 19;
			} else if (this->animationFrame < 60) {
				frame = 20;
			} else if (this->animationFrame < 80) {
				frame = 21;
			} else if (this->animationFrame < 100) {
				frame = 22;
			} else {
				frame = 23;
			}
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, this->level->getScreenX(this->x), this->level->getScreenY(this->y) - 2, this->sprite, this->spriteRegions[frame]);
		}
	}

	SpriteRegion* Zombie::spriteRegions[Zombie::ZOMBIE_NUM_SPRITE_REGIONS];
}

