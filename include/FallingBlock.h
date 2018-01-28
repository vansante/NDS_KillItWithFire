/*
 * FallingBlock.h
 *
 *  Created on: Jun 12, 2011
 *      Author: aeterno
 */

#ifndef FALLINGBLOCK_H_
#define FALLINGBLOCK_H_

#include "GameObject.h"

namespace KIWF{
	typedef enum{
		FBLOCK_STATE_STATIC = 0,
		FBLOCK_STATE_FALLING = 1
	}FallingBlockState;

	class FallingBlock : public GameObject{
		private:
			FallingBlockState state;
			u8 ySpeed;
			u8 fallCounter;

		public:
			FallingBlock(u16 x, u16 y);
			virtual ~FallingBlock();

			void applySpeeds();

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

#endif /* FALLINGBLOCK_H_ */
