/*
 * Fireball.h
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "GameObject.h"

namespace KIWF {
	typedef enum {
		STATE_FLYING,
		STATE_DYING_1,
		STATE_DYING_2,
		STATE_DYING_3,
		STATE_SUPER_FLYING,
		STATE_SUPER_DYING_1,
		STATE_SUPER_DYING_2,
		STATE_SUPER_DYING_3
	} FireballState;

	class Fireball : public GameObject {
	public:
		static const u8 NUM_SPRITE_REGIONS = 12;
		static const u8 SPEED = 4;
		static const u8 START_ENERGY = 24;
		static const u8 ENERGY_DAMAGE = 6;

	private:
		int16 energy;
		FireballState state;
		Direction direction;
		static SpriteRegion* spriteRegions[NUM_SPRITE_REGIONS];
	public:
		Fireball(u16 x, u16 y, Direction direction, bool upgraded);
		virtual ~Fireball();

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

		void draw(Video* video);
	};
}
#endif /* FIREBALL_H_ */
