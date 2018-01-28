/*
 * Sign.h
 *
 *  Created on: 7 jun. 2011
 *      Author: Paul
 */

#ifndef SIGN_H_
#define SIGN_H_

#include <stdio.h>

#include "GameObject.h"
#include "Player.h"
#include "constants.h"

#define PIXEL_VISIBLE(x)		(x | (1 << 15))

namespace KIWF {

	class Sign : public GameObject {
	private:
		bool isShowing;
		const char* signText;
	public:
		static const u16 TEXT_BACKGROUND_COLOR = PIXEL_VISIBLE(0xC210);
		static const u8 ACTIVATE_DISTANCE = 25;

		Sign(u16 x, u16 y);
		virtual ~Sign();

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

		void setSignText();

		void draw(Video* video);
	};

}

#endif /* SIGN_H_ */
