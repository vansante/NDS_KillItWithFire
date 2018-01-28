/*
 * SpriteManager.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "SpriteManager.h"

// Include all the image headers here.
#include "TITLE_SCREEN_SPRITE.h"
#include "CREDITS_SCREEN_SPRITE.h"
#include "LEVEL_SPRITES.h"
#include "MAN_SPRITE.h"
#include "ZOMBIE_SPRITE.h"
#include "FIREBALL_FLY_SPRITE.h"
#include "FIRESTREAM_SPRITE.h"
#include "BURNING_ZOMBIE_SPRITE.h"
#include "DEATH_ZOMBIE_SPRITE.h"
#include "SUPER_ZOMBIE_SPRITE.h"
#include "SUPER_ZOMBIE_BURNING_SPRITE.h"
#include "SUPER_ZOMBIE_DEATH_SPRITE.h"
#include "TOMBSTONE_SPRITE.h"
#include "MUSHROOM_SPRITE.h"
#include "FUEL_BARREL_SPRITE.h"
#include "HAMBURGER_SPRITE.h"
#include "CAKE_SPRITE.h"
#include "LIFE_HEARTS_SPRITE.h"
#include "GAME_OVER_SPRITE.h"
#include "TRY_AGAIN_SPRITE.h"
#include "MMH_CAKE_SPRITE.h"
#include "CRATE_SPRITE.h"
#include "CRATE_BURNING_SPRITE.h"
#include "FALLING_BLOCK_SPRITE.h"
#include "SAVE_POINT_SPRITE.h"
#include "SIGN_SPRITE.h"
#include "FONT_SPRITE.h"
#include "MAN_DEATH_SPRITE.h"

namespace KIWF {

	SpriteManager::SpriteManager() {
		for (u8 i = 0; i < NUM_SPRITES; i++) {
			this->sprites[i] = NULL;
		}
	}
	SpriteManager::~SpriteManager() {}

	Sprite* SpriteManager::get(SpriteId spriteId) {
		if (sprites[spriteId] != NULL) {
			return sprites[spriteId];
		}

		switch (spriteId) {
		case LEVEL_SPRITES:
			sprites[spriteId] = new Sprite(128, 32, ((u16*) LEVEL_SPRITESBitmap));
			break;
		case TITLE_SCREEN_SPRITE:
			sprites[spriteId] = new Sprite(256, 192, ((u16*) TITLE_SCREEN_SPRITEBitmap));
			break;
		case CREDITS_SCREEN_SPRITE:
			sprites[spriteId] = new Sprite(256, 192, ((u16*) CREDITS_SCREEN_SPRITEBitmap));
			break;
		case MAN_SPRITE:
			sprites[spriteId] = new Sprite(60, 64, 20, 32, ((u16*) MAN_SPRITEBitmap));
			break;
		case MAN_DEATH_SPRITE:
			sprites[spriteId] = new Sprite(232, 84, 58, 42, ((u16*) MAN_DEATH_SPRITEBitmap));
			break;
		case ZOMBIE_SPRITE:
			sprites[spriteId] = new Sprite(60, 64, 20, 32, ((u16*) ZOMBIE_SPRITEBitmap));
			break;
		case BURNING_ZOMBIE_SPRITE:
			sprites[spriteId] = new Sprite(72, 70, 24, 35,((u16*) BURNING_ZOMBIE_SPRITEBitmap));
			break;
		case DEATH_ZOMBIE_SPRITE:
			sprites[spriteId] = new Sprite(60, 70, 20, 35, ((u16*) DEATH_ZOMBIE_SPRITEBitmap));
			break;
		case SUPER_ZOMBIE_SPRITE:
			sprites[spriteId] = new Sprite(96,112, 32,56, ((u16*) SUPER_ZOMBIE_SPRITEBitmap));
			break;
		case SUPER_ZOMBIE_BURNING_SPRITE:
			sprites[spriteId] = new Sprite(96,112,32,56,((u16*) SUPER_ZOMBIE_BURNING_SPRITEBitmap));
			break;
		case SUPER_ZOMBIE_DEATH_SPRITE:
			sprites[spriteId] = new Sprite(96,112,32,56, ((u16*) SUPER_ZOMBIE_DEATH_SPRITEBitmap));
			break;
		case FIREBALL_FLY_SPRITE:
			sprites[spriteId] = new Sprite(120, 40, 20, 20, ((u16*) FIREBALL_FLY_SPRITEBitmap));
			break;
		case FIRESTREAM_SPRITE:
			sprites[spriteId] = new Sprite(10, 10, ((u16*) FIRESTREAM_SPRITEBitmap));
			break;
		case TOMBSTONE_SPRITE:
			sprites[spriteId] = new Sprite(96, 96, 24, 32, ((u16*) TOMBSTONE_SPRITEBitmap));
			break;
		case MUSHROOM_SPRITE:
			sprites[spriteId] = new Sprite(20, 20, ((u16*) MUSHROOM_SPRITEBitmap));
			break;
		case FUEL_BARREL_SPRITE:
			sprites[spriteId] = new Sprite(20, 26, ((u16*) FUEL_BARREL_SPRITEBitmap));
			break;
		case HAMBURGER_SPRITE:
			sprites[spriteId] = new Sprite(22, 18, ((u16*) HAMBURGER_SPRITEBitmap));
			break;
		case CAKE_SPRITE:
			sprites[spriteId] = new Sprite(16, 16,((u16*) CAKE_SPRITEBitmap));
			break;
		case LIFE_HEARTS_SPRITE:
			sprites[spriteId] = new Sprite(42, 12, 14, 12, ((u16*) LIFE_HEARTS_SPRITEBitmap));
			break;
		case GAME_OVER_SPRITE:
			sprites[spriteId] = new Sprite(146, 86, ((u16*) GAME_OVER_SPRITEBitmap));
			break;
		case TRY_AGAIN_SPRITE:
			sprites[spriteId] = new Sprite(230, 24, ((u16*) TRY_AGAIN_SPRITEBitmap));
			break;
		case MMH_CAKE_SPRITE:
			sprites[spriteId] = new Sprite(154, 44, ((u16*) MMH_CAKE_SPRITEBitmap));
			break;
		case CRATE_SPRITE:
			sprites[spriteId] = new Sprite(16, 16, ((u16*) CRATE_SPRITEBitmap));
			break;
		case CRATE_BURNING_SPRITE:
			sprites[spriteId] = new Sprite(48, 16, 16, 16, ((u16*) CRATE_BURNING_SPRITEBitmap));
			break;
		case FALLING_BLOCK_SPRITE:
			sprites[spriteId] = new Sprite(16,16,((u16*) FALLING_BLOCK_SPRITEBitmap));
			break;
		case SAVE_POINT_SPRITE:
			sprites[spriteId] = new Sprite(40, 32, 20, 32, ((u16*) SAVE_POINT_SPRITEBitmap));
			break;
		case SIGN_SPRITE:
			sprites[spriteId] = new Sprite(26, 30, ((u16*) SIGN_SPRITEBitmap));
			break;
		case FONT_SPRITE:
			sprites[spriteId] = new Sprite(112, 78, 7, 13, ((u16*) FONT_SPRITEBitmap));
			break;
		}
		return sprites[spriteId];
	}
}
