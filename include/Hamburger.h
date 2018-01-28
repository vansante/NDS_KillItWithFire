/*
 * Hamburger.h
 *
 *  Created on: 5 jun. 2011
 *      Author: Paul
 */

#ifndef HAMBURGER_H_
#define HAMBURGER_H_

#include "GameObject.h"

namespace KIWF {

	class Hamburger : public GameObject {
	public:
		static const u8 MAX_HEALTH = 100;
		static const u8 RESTORED_HEALTH_AMOUNT = 100;
	private:
		int16 health;
	public:
		Hamburger(u16 x, u16 y);
		virtual ~Hamburger();

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

#endif /* HAMBURGER_H_ */
