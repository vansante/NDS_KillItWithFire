/*
 * BurnableBlock.h
 *
 *  Created on: Jun 11, 2011
 *      Author: aeterno
 */

#ifndef BURNABLEBLOCK_H_
#define BURNABLEBLOCK_H_

#include "GameObject.h"
#include "SpriteManager.h"

namespace KIWF{

	typedef enum{
		BLOCK_NORMAL = 0,
		BLOCK_BURNING = 1,
	} BurnableBlockState;

	class BurnableBlock : public GameObject{
	public:
		static const u8 MAX_HEALTH = 100;
	private:
		int16 health;
		static const u8 NUM_SPRITE_REGIONS = 3;
		static SpriteRegion* spriteRegions[NUM_SPRITE_REGIONS];
		BurnableBlockState state;

		u8 animationFrame;
	public:
		BurnableBlock(u16 x, u16 y);
		virtual ~BurnableBlock();

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

#endif /* BURNABLEBLOCK_H_ */
