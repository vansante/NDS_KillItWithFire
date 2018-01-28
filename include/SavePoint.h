/*
 * SavePoint.h
 *
 *  Created on: 13 jun. 2011
 *      Author: Paul
 */

#ifndef SAVEPOINT_H_
#define SAVEPOINT_H_

#include "GameObject.h"
#include "Player.h"
#include "constants.h"

namespace KIWF {

	class SavePoint : public GameObject {
	public:
		static const u8 ACTIVATE_DISTANCE = 25;
		static const u8 SAVE_POINT_NUM_SPRITE_REGIONS = 2;
	private:
		bool isSaved;

		static SpriteRegion* spriteRegions[SAVE_POINT_NUM_SPRITE_REGIONS];

	public:
		SavePoint(u16 x, u16 y);
		virtual ~SavePoint();

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

#endif /* SAVEPOINT_H_ */
