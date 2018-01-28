/*
 * SpriteManager.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <nds.h>

#include "Sprite.h"

namespace KIWF {

	typedef enum {
		TITLE_SCREEN_SPRITE,
		CREDITS_SCREEN_SPRITE,
		LEVEL_SPRITES,
		MAN_SPRITE,
		MAN_DEATH_SPRITE,
		ZOMBIE_SPRITE,
		BURNING_ZOMBIE_SPRITE,
		DEATH_ZOMBIE_SPRITE,
		SUPER_ZOMBIE_SPRITE,
		SUPER_ZOMBIE_BURNING_SPRITE,
		SUPER_ZOMBIE_DEATH_SPRITE,
		FIREBALL_FLY_SPRITE,
		FIRESTREAM_SPRITE,
		TOMBSTONE_SPRITE,
		MUSHROOM_SPRITE,
		HAMBURGER_SPRITE,
		FUEL_BARREL_SPRITE,
		LIFE_HEARTS_SPRITE,
		GAME_OVER_SPRITE,
		TRY_AGAIN_SPRITE,
		MMH_CAKE_SPRITE,
		CAKE_SPRITE,
		CRATE_SPRITE,
		CRATE_BURNING_SPRITE,
		FALLING_BLOCK_SPRITE,
		SAVE_POINT_SPRITE,
		SIGN_SPRITE,
		FONT_SPRITE
	} SpriteId;

	class SpriteManager {
	public:
		static const u8 NUM_SPRITES = 28;
	private:
		static SpriteManager* instance;

		Sprite* sprites[NUM_SPRITES];

		SpriteManager();
		SpriteManager(SpriteManager const&);	// Don't Implement
		void operator=(SpriteManager const&); 	// Don't implement

	public:
		virtual ~SpriteManager();

		static SpriteManager& getInstance() {
			static SpriteManager instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}

		Sprite* get(SpriteId spriteId);
	};
}

#endif /* SPRITEMANAGER_H_ */
