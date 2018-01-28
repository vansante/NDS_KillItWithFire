/*
 * Tombstone.h
 *
 *  Created on: Jun 4, 2011
 *      Author: aeterno
 */

#ifndef TOMBSTONE_H_
#define TOMBSTONE_H_

#include "Zombie.h"
#include "GameObject.h"
#include "Level.h"
#include "Video.h"
#include "SoundManager.h"

namespace KIWF {

	typedef enum {
		STATE_WOOD = 0,
		STATE_WOOD_BURNING = 1,
		STATE_WOOD_DYING = 2,
		STATE_STONE = 3,
		STATE_GOLDEN = 4
	} TombstoneState;

	class Tombstone : public GameObject {
	public:
		static const u16 FRAMES_PER_SPAWN = 800;
		static const u8 NUM_SPRITE_REGIONS = 11;
	private:
		u8 zombies;
		u16 counter;
		Level* level;

		int16 health;

		u8 animationFrame;
		static SpriteRegion* spriteRegions[NUM_SPRITE_REGIONS];
		TombstoneState state;
	public:
		Tombstone(u16 x,u16 y, Level* level, TombstoneState state = STATE_WOOD);
		virtual ~Tombstone();

		void interact(Drawable* drawable);
		void destroy();
		void bite(u16 damage);
		void burn(u16 damage);
		void upgrade();
		void fuel(u16 amount);
		void heal(u16 amount);
		void cake();
		void doAction();
		void enterActiveList();

		void reduceHealth(u8 amount);

		void draw(Video* video);
	};

}
#endif /* TOMBSTONE_H_ */
