/*
 * Cake.h
 *
 *  Created on: Jun 8, 2011
 *      Author: aeterno
 */

#ifndef CAKE_H_
#define CAKE_H_

#include "Video.h"
#include "Drawable.h"
#include "GameObject.h"

namespace KIWF {
	class Cake : public GameObject {
		public:
		Cake(u16 x, u16 y);
		virtual ~Cake();

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

#endif /* CAKE_H_ */
