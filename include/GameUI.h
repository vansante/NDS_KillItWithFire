/*
 * GameUI.h
 *
 *  Created on: 1 jun. 2011
 *      Author: Paul
 */

#ifndef GAMEUI_H_
#define GAMEUI_H_

#include "Screen.h"
#include "Video.h"
#include "Level.h"
#include "Player.h"

#define PIXEL_VISIBLE(x)		(x | (1 << 15))

namespace KIWF {

	typedef enum {
		REGION_HEART_FULL,
		REGION_HEART_HALF,
		REGION_HEART_EMPTY
	} HeartSpriteRegionId;

	class GameUI {
	public:
		static const u8 NUM_HEART_SPRITE_REGIONS = 3;

		static const u8 NUM_HEARTS = 5;
		static const u8 FIRST_HEART_X = 4;
		static const u8 FIRST_HEART_Y = 2;
		static const u8 HEART_MARGIN = 1;

		static const u8 FUEL_BAR_X = 202;
		static const u8 FUEL_BAR_Y = 4;
		static const u8 FUEL_BAR_WIDTH = 50;
		static const u8 FUEL_BAR_HEIGHT = 8;
		static const u16 FUEL_BAR_OUTER_COLOR = PIXEL_VISIBLE(0xFFFF);
		static const u16 FUEL_BAR_INNER_COLOR = PIXEL_VISIBLE(0xFF40);
	private:
		Sprite* gameOverSprite;
		Sprite* tryAgainSprite;
		Sprite* cakeSprite;
		Sprite* heartSprite;

		SpriteRegion* heartSpriteRegions[NUM_HEART_SPRITE_REGIONS];
		Level* level;

	public:
		GameUI(Level* level);
		virtual ~GameUI();

		void drawUI(Video* video);
		void drawFuelBar(Video* video);
		void drawLifeHearts(Video* video);
		void drawGameOver(Video* video);
		void drawEatingCake(Video* video);
	};

}

#endif /* GAMEUI_H_ */
