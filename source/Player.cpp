/*
 * Player.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "Player.h"
#include "constants.h"
#include "Fireball.h"
#include "Firestream.h"
#include "SoundManager.h"

namespace KIWF {

	Player::Player(Level* level, u16 startX, u16 startY) {
		this->level = level;
		this->x = startX;
		this->y = startY;

		this->health = MAX_HEALTH;
		this->fuelLevel = MAX_FUEL_LEVEL;
		this->blueFireball = false;
		this->state = STATE_ALIVE;
		this->direction = DIRECTION_RIGHT;
		this->drawPriority = PRIORITY_1;

		this->frameCounter = 0;
		this->animationFrame = 0;

		this->sprite = SpriteManager::getInstance().get(MAN_SPRITE);

		// Direction left
		this->spriteRegions[0] = new SpriteRegion(0, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		this->spriteRegions[1] = new SpriteRegion(20, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		this->spriteRegions[2] = new SpriteRegion(40, 0, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		// Direction right
		this->spriteRegions[3] = new SpriteRegion(0, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		this->spriteRegions[4] = new SpriteRegion(20, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());
		this->spriteRegions[5] = new SpriteRegion(40, 32, this->sprite->getTileWidth(), this->sprite->getTileHeight());

		//	Death animation
		this->spriteRegions[6] = new SpriteRegion(0, 0, 58, 42);
		this->spriteRegions[7] = new SpriteRegion(58, 0, 58, 42);
		this->spriteRegions[8] = new SpriteRegion(116, 0, 58, 42);
		this->spriteRegions[9] = new SpriteRegion(172, 0, 58, 42);
		this->spriteRegions[10] = new SpriteRegion(0, 42, 58, 42);
		this->spriteRegions[11] = new SpriteRegion(58, 42, 58, 42);
		this->spriteRegions[12] = new SpriteRegion(116, 42, 58, 42);
		this->spriteRegions[13] = new SpriteRegion(174, 42, 58, 42);
	}

	Player::~Player() {}

	u16 Player::getCenterX() {
		return this->x + (this->sprite->getTileWidth() / 2);
	}

	u16 Player::getCenterY() {
		return this->y + (this->sprite->getTileHeight() / 2);
	}

	void Player::setX(u16 x){
		this->x = x;
	}

	void Player::setY(u16 y) {
		this->y = y;
	}

	u16 Player::getWidth() {
		return this->sprite->getTileWidth();
	}
	u16 Player::getHeight() {
		return this->sprite->getTileHeight();
	}

	u16 Player::getFuelLevel() {
		return this->fuelLevel;
	}

	u8 Player::getHealth() {
		return this->health;
	}

	PlayerState Player::getState(){
		return this->state;
	}

	void Player::reduceHealth(u8 amount) {
		if (this->state == STATE_ALIVE) {
			this->health -= amount;
			if (this->health < 0) {
				#ifdef CHEAT_DEATH
					// Magically resurrect
					this->health = MAX_HEALTH;
				#else
					this->health = 0;
					this->state = STATE_DEATH_ANIMATION;
					this->sprite = SpriteManager::getInstance().get(MAN_DEATH_SPRITE);

					//	Offset a bit because the death animation has a larger sprite.
					this->y -= 10;
					this->x -= 11;

					//	Set animation frame to zero so we begin at the correct point.
					this->animationFrame = 0;
				#endif
			}
		}
	}

	void Player::diminishXSpeed() {
		if (this->xSpeed < 0) {
			this->xSpeed++;
		} else if (this->xSpeed > 0) {
			this->xSpeed--;
		}
	}

	void Player::applyGravity() {
		u8 type = this->level->detectLevelCollision(this->x, this->y + 1, this->sprite->getTileWidth(), this->sprite->getTileHeight());

		if (this->frameCounter % 3 == 0) {
			if (type == COLLIDE_NONE || (type & COLLIDE_LAVA && !(type & COLLIDE_TERRAIN)) || (type & COLLIDE_SPIKES && !(type & COLLIDE_TERRAIN))) {
				this->ySpeed++;
				if (this->ySpeed > 10) {
					this->ySpeed = 10;
				}
			}
		}
	}

	void Player::applySpeeds() {
		u8 type;

		// If were currently in the shit, apply damage.
		type = this->level->detectLevelCollision(
			this->x, this->y,
			this->sprite->getTileWidth(), this->sprite->getTileHeight()
		);
		if (type & COLLIDE_LAVA) {
			this->reduceHealth(LAVA_DAMAGE);
		}
		if (type & COLLIDE_SPIKES) {
			this->reduceHealth(SPIKE_DAMAGE);
		}

		type = this->level->detectLevelCollision(
			this->x + this->xSpeed, this->y + this->ySpeed,
			this->sprite->getTileWidth(), this->sprite->getTileHeight()
		);
		if (!(type & COLLIDE_EDGE) && !(type & COLLIDE_TERRAIN) && !(type & COLLIDE_OBJECT)) {
			this->x += this->xSpeed;
			this->y += this->ySpeed;
		} else {
			type = this->level->detectLevelCollision(
				this->x, this->y + this->ySpeed,
				this->sprite->getTileWidth(), this->sprite->getTileHeight()
			);

			if (!(type & COLLIDE_EDGE) && !(type & COLLIDE_TERRAIN) && !(type & COLLIDE_OBJECT)) {
				this->xSpeed = 0;
			} else {
				type = this->level->detectLevelCollision(
					this->x + this->xSpeed, this->y,
					this->sprite->getTileWidth(), this->sprite->getTileHeight()
				);

				if (!(type & COLLIDE_EDGE) && !(type & COLLIDE_TERRAIN) && !(type & COLLIDE_OBJECT)) {
					this->ySpeed = 0;
				} else {
					this->xSpeed = 0;
					this->ySpeed = 0;
				}
			}
			this->x += this->xSpeed;
			this->y += this->ySpeed;
		}
	}

	void Player::goLeft() {
		this->xSpeed--;
		if (xSpeed < 0) {
			this->direction = DIRECTION_LEFT;
		}
		if (xSpeed < -2) {
			xSpeed = -2;
		}
	}

	void Player::goRight() {
		this->xSpeed++;
		if (this->xSpeed > 0) {
			this->direction = DIRECTION_RIGHT;
		}
		if (this->xSpeed > 2) {
			this->xSpeed = 2;
		}
	}

	bool Player::engageRocket() {
		if (this->fuelLevel < ROCKET_FUEL_COST * 3) {
			return false;
		}
		this->fuelLevel -= ROCKET_FUEL_COST;
		this->ySpeed -= ROCKET_SPEED;
		if (this->ySpeed < - ROCKET_SPEED) {
			this->ySpeed = - ROCKET_SPEED;
		}

		if (this->frameCounter % 4 == 0) {
			if (direction == DIRECTION_LEFT) {
				this->level->addObject(new Firestream(this->x + 15, this->y + this->sprite->getTileHeight()));
			} else {
				this->level->addObject(new Firestream(this->x - 5, this->y + this->sprite->getTileHeight()));
			}
		}

		if (this->frameCounter % 30 == 0) {
			// Only play sound every 0.5 seconds
			SoundManager::getInstance().playSound(SFX_ROCKET_ENGAGE);
		}
		return true;
	}

	bool Player::shootFireball(Direction direction) {
		if (this->fuelLevel < FIREBALL_FUEL_COST) {
			return false;
		}
		this->fuelLevel -= FIREBALL_FUEL_COST;
		u16 ballX = this->x;
		u16 ballY = this->y;

		switch (direction) {
		case DIRECTION_UP:
			ballX = this->getCenterX() - 8;
			ballY -= 18;
			break;
		case DIRECTION_DOWN:
			ballX = this->getCenterX() - 8;
			ballY += this->sprite->getTileHeight() - 2;
			break;
		case DIRECTION_LEFT:
			ballX -= 18;
			ballY = this->getCenterY() - 8;
			break;
		case DIRECTION_RIGHT:
			ballX += this->sprite->getTileWidth() - 2;
			ballY = this->getCenterY() - 8;
			break;
		default:
			return false;
		}
		this->level->addObject(new Fireball(ballX, ballY, direction, this->blueFireball));
		this->blueFireball = false;

		SoundManager::getInstance().playSound(SFX_FIREBALL_LAUNCH);
		return true;
	}

	void Player::doMovements(u16 keysDown, u16 keysHeld) {
		if (this->state == STATE_ALIVE) {
			this->frameCounter++;
			if (this->frameCounter >= 251) {
				this->frameCounter = 0;
			}

			bool directionPressed = true;
			bool isFlying = false;
			Direction keyDirection = DIRECTION_LEFT;

			if (keysHeld & KEY_UP) {
				if (keysHeld & KEY_LEFT) {
					keyDirection = DIRECTION_UP_LEFT;
				} else if (keysHeld & KEY_RIGHT) {
					keyDirection = DIRECTION_UP_RIGHT;
				} else {
					keyDirection = DIRECTION_UP;
				}
			} else if (keysHeld & KEY_DOWN) {
				if (keysHeld & KEY_LEFT) {
					keyDirection = DIRECTION_DOWN_LEFT;
				} else if (keysHeld & KEY_RIGHT) {
					keyDirection = DIRECTION_DOWN_RIGHT;
				} else {
					keyDirection = DIRECTION_DOWN;
				}
			} else if (keysHeld & KEY_LEFT) {
				keyDirection = DIRECTION_LEFT;
			} else if (keysHeld & KEY_RIGHT) {
				keyDirection = DIRECTION_RIGHT;
			} else {
				directionPressed = false;
			}

			if (keysDown & KEY_A || keysHeld & KEY_A) {
				isFlying = this->engageRocket();
			}
			this->applyGravity();

			if (directionPressed) {
				switch (keyDirection) {
				case DIRECTION_LEFT:
				case DIRECTION_UP_LEFT:
				case DIRECTION_DOWN_LEFT:
					this->goLeft();
					if (!isFlying) {
						this->animationFrame++;
						this->animationFrame %= 23;
					}
					break;
				case DIRECTION_RIGHT:
				case DIRECTION_UP_RIGHT:
				case DIRECTION_DOWN_RIGHT:
					this->goRight();
					if (!isFlying) {
						this->animationFrame++;
						this->animationFrame %= 23;
					}
					break;
				default:
					this->diminishXSpeed();
					break;
				}
			} else {
				this->diminishXSpeed();
			}

			this->applySpeeds();

			if (keysDown & KEY_B) {
				if (directionPressed) {
					switch (keyDirection) {
					case DIRECTION_UP:
						this->shootFireball(DIRECTION_UP);
						break;
					case DIRECTION_DOWN:
						this->shootFireball(DIRECTION_DOWN);
						break;
					case DIRECTION_LEFT:
					case DIRECTION_UP_LEFT:
					case DIRECTION_DOWN_LEFT:
						this->shootFireball(DIRECTION_LEFT);
						break;
					case DIRECTION_RIGHT:
					case DIRECTION_UP_RIGHT:
					case DIRECTION_DOWN_RIGHT:
						this->shootFireball(DIRECTION_RIGHT);
						break;
					}
				} else {
					this->shootFireball(this->direction);
				}
			}

			this->fuelLevel += FUEL_RECOVERED_EVERY_FRAME;
			if (this->fuelLevel > MAX_FUEL_LEVEL) {
				this->fuelLevel = MAX_FUEL_LEVEL;
			}
			#ifdef INFINITE_FUEL
				this->fuelLevel = MAX_FUEL_LEVEL;
			#endif
		} else if (this->state == STATE_DEATH_ANIMATION) {
			this->animationFrame++;
			if (this->animationFrame >= 60) {
				this->state = STATE_DEAD;
			}
		} else if (this->state == STATE_DEAD) {
			if (keysDown & KEY_A) {
				this->state = STATE_ALIVE;
				this->health = MAX_HEALTH;
				this->fuelLevel = MAX_FUEL_LEVEL;
				this->animationFrame = 0;
				this->frameCounter = 0;
				this->blueFireball = false;
				this->sprite = SpriteManager::getInstance().get(MAN_SPRITE);
				this->level->respawnPlayer();
			}
		} else if (this->state == STATE_EATING_CAKE) {
			if (this->frameCounter < 250) {
				this->frameCounter++;
			} else {
				SoundManager::getInstance().playSound(SFX_CAKE_EATEN);
				this->frameCounter = 0;
			}
		}
	}

	void Player::destroy() {
		this->health = 0;
	}

	void Player::bite(u16 damage) {
		this->reduceHealth(damage);
	}

	void Player::burn(u16 damage) {}

	void Player::upgrade() {
		this->blueFireball = true;
	}

	void Player::fuel(u16 amount) {
		this->fuelLevel += amount;
		if (this->fuelLevel >= MAX_FUEL_LEVEL) {
			this->fuelLevel = MAX_FUEL_LEVEL;
		}
	}

	void Player::heal(u16 amount) {
		this->health += amount;
		if (this->health >= MAX_HEALTH) {
			this->health = MAX_HEALTH;
		}
	}

	void Player::cake() {
		if (this->state != STATE_EATING_CAKE) {
			this->state = STATE_EATING_CAKE;
			this->frameCounter = 0;
		}
	}

	void Player::draw(Video* video) {
		switch (this->state) {
		case STATE_ALIVE:
		case STATE_EATING_CAKE:
			video->drawSprite(
				MAIN_SCREEN_FOREGROUND,
				false,
				this->level->getScreenX(this->x),
				this->level->getScreenY(this->y),
				this->sprite,
				this->spriteRegions[this->direction * 3 + this->animationFrame / 8]
			);
			break;
		case STATE_DEAD:
			video->drawSprite(
				MAIN_SCREEN_FOREGROUND,
				false,
				this->level->getScreenX(this->x),
				this->level->getScreenY(this->y),
				this->sprite,
				this->spriteRegions[13]
			);
			break;
		case STATE_DEATH_ANIMATION:
			u8 frame = 6 + this->animationFrame / 10;
			video->drawSprite(
				MAIN_SCREEN_FOREGROUND,
				false,
				this->level->getScreenX(this->x),
				this->level->getScreenY(this->y),
				this->sprite,
				this->spriteRegions[frame]
			);
			break;
		}
	}
}
