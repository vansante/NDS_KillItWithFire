/*
 * Player.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <nds.h>

#include "Drawable.h"
#include "SpriteManager.h"
#include "SpriteRegion.h"

namespace KIWF {
	// Forward declaration of Level for cyclic dependency
	class Level;

	typedef enum {
		STATE_ALIVE,
		STATE_EATING_CAKE,
		STATE_DEATH_ANIMATION,
		STATE_DEAD
	} PlayerState;

	class Player : public Drawable {
	public:
		static const u8 NUM_SPRITE_REGIONS = 14;

		static const u8 MAX_HEALTH = 100;
		static const u8 SPIKE_DAMAGE = 1;
		static const u8 LAVA_DAMAGE = 2;

		static const u16 MAX_FUEL_LEVEL = 2500;
		static const u8 FUEL_RECOVERED_EVERY_FRAME = 1;
		static const u8 ROCKET_FUEL_COST = 8;
		static const u8 FIREBALL_FUEL_COST = 30;
		static const u8 ROCKET_SPEED = 2;

	private:
		u16 fuelLevel;
		int16 health;

		int8 xSpeed;
		int8 ySpeed;

		u8 frameCounter;
		u8 animationFrame;

		bool blueFireball;
		PlayerState state;
		Direction direction;

		Level* level;

		SpriteRegion* spriteRegions[NUM_SPRITE_REGIONS];

	public:
		Player(Level* level, u16 startX, u16 startY);
		virtual ~Player();

		u16 getCenterX();
		u16 getCenterY();
		void setX(u16 x);
		void setY(u16 y);
		u16 getWidth();
		u16 getHeight();
		u16 getFuelLevel();
		u8 getHealth();
		PlayerState getState();
		void reduceHealth(u8 amount);

		void diminishXSpeed();
		void applyGravity();
		void applySpeeds();

		void goLeft();
		void goRight();
		bool engageRocket();
		bool shootFireball(Direction direction);

		void doMovements(u16 keysDown, u16 keysHeld);

		void destroy();
		void bite(u16 damage);
		void burn(u16 damage);
		void upgrade();
		void fuel(u16 amount);
		void heal(u16 amount);
		void cake();

		void draw(Video* video);
	};

}

#include "Level.h"
#endif /* PLAYER_H_ */
