/*
 * Mushroom.h
 *
 *  Created on: 4 jun. 2011
 *      Author: Paul
 */

#ifndef MUSHROOM_H_
#define MUSHROOM_H_

#include "GameObject.h"

namespace KIWF {

	class Mushroom : public GameObject {
	public:
		static const u8 MAX_HEALTH = 100;
	private:
		int16 health;
	public:
		Mushroom(u16 x, u16 y);
		virtual ~Mushroom();

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

#endif /* MUSHROOM_H_ */
