/*
 * Firestream.h
 *
 *  Created on: 4 jun. 2011
 *      Author: Paul
 */

#ifndef FIRESTREAM_H_
#define FIRESTREAM_H_

#include "GameObject.h"

namespace KIWF {

	class Firestream : public GameObject {
	public:
		static const u8 SPEED = 4;
		static const u8 START_ENERGY = 20;
		static const u8 ENERGY_DAMAGE = 4;
	private:
		int8 energy;
	public:
		Firestream(u16 x, u16 y);
		virtual ~Firestream();

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

#endif /* FIRESTREAM_H_ */
