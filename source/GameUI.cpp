/*
 * GameUI.cpp
 *
 *  Created on: 1 jun. 2011
 *      Author: Paul
 */

#include "GameUI.h"

namespace KIWF {

	GameUI::GameUI(Level* level) {
		this->level = level;

		this->gameOverSprite = SpriteManager::getInstance().get(GAME_OVER_SPRITE);
		this->tryAgainSprite = SpriteManager::getInstance().get(TRY_AGAIN_SPRITE);
		this->cakeSprite = SpriteManager::getInstance().get(MMH_CAKE_SPRITE);
		this->heartSprite = SpriteManager::getInstance().get(LIFE_HEARTS_SPRITE);

		this->heartSpriteRegions[REGION_HEART_FULL] = new SpriteRegion(0, 0, this->heartSprite->getTileWidth(), this->heartSprite->getTileHeight());
		this->heartSpriteRegions[REGION_HEART_HALF] = new SpriteRegion(14, 0, this->heartSprite->getTileWidth(), this->heartSprite->getTileHeight());
		this->heartSpriteRegions[REGION_HEART_EMPTY] = new SpriteRegion(28, 0, this->heartSprite->getTileWidth(), this->heartSprite->getTileHeight());
	}

	GameUI::~GameUI() {
		for (u8 i = 0; i < NUM_HEART_SPRITE_REGIONS; i++) {
			free(this->heartSpriteRegions[i]);
		}
	}

	void GameUI::drawUI(Video* video) {
		switch (this->level->getPlayer()->getState()) {
		case STATE_DEATH_ANIMATION:
		case STATE_ALIVE:
			this->drawLifeHearts(video);
			this->drawFuelBar(video);
			break;
		case STATE_DEAD:
			this->drawGameOver(video);
			break;
		case STATE_EATING_CAKE:
			this->drawEatingCake(video);
			break;
		}
	}

	void GameUI::drawLifeHearts(Video* video) {
		u8 health = this->level->getPlayer()->getHealth();

		u8 screenX, spriteHeartRegion;
		for (u8 heart = 0; heart < NUM_HEARTS; heart++) {
			screenX = FIRST_HEART_X + heart * (this->heartSprite->getTileWidth() + HEART_MARGIN);
			if (health >= Player::MAX_HEALTH / NUM_HEARTS * (heart + 1)) {
				spriteHeartRegion = REGION_HEART_FULL;
			} else if (health >= Player::MAX_HEALTH / NUM_HEARTS * (heart + 1) - (Player::MAX_HEALTH / NUM_HEARTS / 2)) {
				spriteHeartRegion = REGION_HEART_HALF;
			} else {
				spriteHeartRegion = REGION_HEART_EMPTY;
			}
			video->drawSprite(MAIN_SCREEN_FOREGROUND, false, screenX, FIRST_HEART_Y, this->heartSprite, this->heartSpriteRegions[spriteHeartRegion]);
		}
	}

	void GameUI::drawFuelBar(Video* video) {
		u16 fuelLevel = this->level->getPlayer()->getFuelLevel();

		// Draw the outer lines
		video->drawLineHorizontal(MAIN_SCREEN_FOREGROUND, FUEL_BAR_X, FUEL_BAR_Y, FUEL_BAR_WIDTH, FUEL_BAR_OUTER_COLOR);
		video->drawLineHorizontal(MAIN_SCREEN_FOREGROUND, FUEL_BAR_X, FUEL_BAR_Y + FUEL_BAR_HEIGHT, FUEL_BAR_WIDTH, FUEL_BAR_OUTER_COLOR);
		video->drawLineVertical(MAIN_SCREEN_FOREGROUND, FUEL_BAR_X, FUEL_BAR_Y, FUEL_BAR_HEIGHT, FUEL_BAR_OUTER_COLOR);
		video->drawLineVertical(MAIN_SCREEN_FOREGROUND, FUEL_BAR_X + FUEL_BAR_WIDTH, FUEL_BAR_Y, FUEL_BAR_HEIGHT + 1, FUEL_BAR_OUTER_COLOR);

		// Print actual fuel level
		if (fuelLevel > 0) {
			// Calculate fuelLevel % in pixels
			fuelLevel = fuelLevel * (FUEL_BAR_WIDTH - 2) / Player::MAX_FUEL_LEVEL;
			for (u16 y = FUEL_BAR_Y + 1; y < FUEL_BAR_Y + FUEL_BAR_HEIGHT; y++) {
				video->drawLineHorizontal(MAIN_SCREEN_FOREGROUND, FUEL_BAR_X + 1, y, fuelLevel + 1, FUEL_BAR_INNER_COLOR);
			}
		}
	}

	void GameUI::drawGameOver(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, false, 55, 25, this->gameOverSprite);
		video->drawSprite(MAIN_SCREEN_FOREGROUND, false, 13, 148, this->tryAgainSprite);
	}

	void GameUI::drawEatingCake(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, false, 51, 74, this->cakeSprite);
	}
}
