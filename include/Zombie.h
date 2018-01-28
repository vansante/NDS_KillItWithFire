/*
 * Zombie.h
 *
 *  Created on: Jun 4, 2011
 *      Author: aeterno
 */

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "GameObject.h"
#include "SoundManager.h"

namespace KIWF{

	typedef enum{
		STATE_NORMAL = 0,
		STATE_BURNING = 1,
		STATE_DYING = 2,
		STATE_SUPER_NORMAL = 3,
		STATE_SUPER_BURNING = 4,
		STATE_SUPER_DYING = 5
	} ZombieState;

	class Zombie : public GameObject{
	public:
		static const u16 SUPER_MAX_HEALTH = 760;
		static const u16 MAX_HEALTH = 380;
		static const u8 ZOMBIE_NUM_SPRITE_REGIONS = 24;
		static const u8 BURN_DAMAGE = 1;
		static const u8 LAVA_MELT_DAMAGE = 3;
		static const u8 ZOMBIE_WIDTH = 20;
		static const u8 ZOMBIE_HEIGHT = 32;
		static const u8 ZOMBIE_DAMAGE = 1;

		Zombie(u16 x, u16 y, Direction direction, bool allowCleanUp, ZombieState state = STATE_NORMAL);
		virtual ~Zombie();

		void reduceHealth(u8 amount);

		void enterActiveList();
		void interact(Drawable* drawable);
		void destroy();
		void bite(u16 damage);
		void burn(u16 damage);
		void upgrade();
		void fuel(u16 amount);
		void heal(u16 amount);
		void cake();
		void doAction();

		void reverseDirection();

		void draw(Video* video);
	private:
		static SpriteRegion* spriteRegions[ZOMBIE_NUM_SPRITE_REGIONS];

		u8 speed;
		int16 health;
		u8 animationFrame;
		int8 xSpeed;
		int8 ySpeed;
		Direction direction;
		ZombieState state;

		int16 stalkerLevel;

		void jump();
		void applyGravity();
	};
}

#endif /* ZOMBIE_H_ */
