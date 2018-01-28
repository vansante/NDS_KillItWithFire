/*
 * FuelBarrel.h
 *
 *  Created on: 5 jun. 2011
 *      Author: Paul
 */

#ifndef FUELBARREL_H_
#define FUELBARREL_H_

#include "GameObject.h"
#include "Player.h"

namespace KIWF {

	class FuelBarrel : public GameObject {
	public:
		static const u8 MAX_HEALTH = 100;
		static const u16 FUEL_AMOUNT = Player::MAX_FUEL_LEVEL;
	private:
		int16 health;
	public:
		FuelBarrel(u16 x, u16 y);
		virtual ~FuelBarrel();

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

#endif /* FUELBARREL_H_ */
