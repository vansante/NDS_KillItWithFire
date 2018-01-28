/*
 * Level.cpp
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#include "Level.h"
#include "Sign.h"
#include "SavePoint.h"
#include "Zombie.h"
#include "Tombstone.h"
#include "Mushroom.h"
#include "FuelBarrel.h"
#include "Hamburger.h"
#include "Cake.h"
#include "BurnableBlock.h"
#include "FallingBlock.h"

namespace KIWF {

	Level::Level(Video* video) {
		this->frame = 0;
		this->levelData = (u16*) LEVEL_DATABitmap;
		this->tilesSprite = SpriteManager::getInstance().get(LEVEL_SPRITES);

		this->objects = new GameObjects();

		this->spriteRegions[REGION_GROUND] = new SpriteRegion(0, 0, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_CEILING_ROUNDED_LEFT] = new SpriteRegion(16, 0, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_CEILING_ROUNDED_RIGHT] = new SpriteRegion(32, 0, SPRITE_SIZE, SPRITE_SIZE);

		this->spriteRegions[REGION_FLOOR] = new SpriteRegion(48, 0, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_FLOOR_ROUNDED_LEFT] = new SpriteRegion(64, 0, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_FLOOR_ROUNDED_RIGHT] = new SpriteRegion(80, 0, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_NONE] = new SpriteRegion(112, 0, SPRITE_SIZE, SPRITE_SIZE);

		this->spriteRegions[REGION_FLOOR_SPIKES] = new SpriteRegion(0, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_ROOF_SPIKES] = new SpriteRegion(16, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_WALL_SPIKES_LEFT] = new SpriteRegion(32, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_WALL_SPIKES_RIGHT] = new SpriteRegion(48, 16, SPRITE_SIZE, SPRITE_SIZE);

		this->spriteRegions[REGION_LAVA] = new SpriteRegion(64, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_LAVA_SURFACE_1] = new SpriteRegion(80, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_LAVA_SURFACE_2] = new SpriteRegion(96, 16, SPRITE_SIZE, SPRITE_SIZE);
		this->spriteRegions[REGION_LAVA_SURFACE_3] = new SpriteRegion(112, 16, SPRITE_SIZE, SPRITE_SIZE);

		this->createPlayer();

		this->levelBuffer = video->getBuffer(MAIN_SCREEN_BACKGROUND);
		this->initializeLevelBuffer();

		this->instantiateLevelGameObjects();
	}

	Level::~Level() {
		free(this->levelBuffer);
	}

	void Level::createPlayer() {
		u16 levelX, levelY;
		this->playerSpawnX = 30;
		this->playerSpawnY = 30;

		// Search spawn point
		for (levelX = 0; levelX < LEVEL_WIDTH; levelX++) {
			for (levelY = 0; levelY < LEVEL_HEIGHT; levelY++) {
				if (this->levelData[levelY * LEVEL_WIDTH + levelX] == ID_PLAYER_SPAWN) {
					this->playerSpawnX = levelX * SPRITE_SIZE;
					this->playerSpawnY = levelY * SPRITE_SIZE - SPRITE_SIZE;
				}
			}
		}
		this->player = new Player(this, this->playerSpawnX, playerSpawnY);
	}

	void Level::setPlayerSpawn(u16 x, u16 y) {
		this->playerSpawnX = x;
		this->playerSpawnY = y;
	}

	void Level::respawnPlayer(){
		//	Destroy the gameObjects
		this->objects->destroyAll();

		//	Set the player coordinates to the spawn position:
		this->player->setX(this->playerSpawnX);
		this->player->setY(this->playerSpawnY);

		this->instantiateLevelGameObjects();
		this->initializeLevelBuffer();
	}

	void Level::instantiateLevelGameObjects() {
		u16 levelX, levelY, screenX, screenY, curTile;

		for (levelX = 0; levelX < LEVEL_WIDTH; levelX++) {
			for (levelY = 0; levelY < LEVEL_HEIGHT; levelY++) {
				screenX = levelX * SPRITE_SIZE;
				screenY = levelY * SPRITE_SIZE;
				curTile = this->levelData[levelY * LEVEL_WIDTH + levelX];

				switch (curTile) {
				case ID_WOODEN_BLOCK:
					this->addObject(new BurnableBlock(screenX, screenY));
					break;
				case ID_FALLING_BLOCK:
					this->addObject(new FallingBlock(screenX, screenY));
					break;
				case ID_SIGN:
					this->addObject(new Sign(screenX - 5, screenY - 14));
					break;
				case ID_PLAYER_SAVE:
					this->addObject(new SavePoint(screenX - 2, screenY - 16));
					break;
				case ID_FUEL_BARREL:
					this->addObject(new FuelBarrel(screenX - 2, screenY - 10));
					break;
				case ID_MUSHROOM:
					this->addObject(new Mushroom(screenX - 2, screenY - 4));
					break;
				case ID_HAMBURGER:
					this->addObject(new Hamburger(screenX - 3, screenY - 2));
					break;
				case ID_CAKE:
					this->addObject(new Cake(screenX, screenY));
					break;
				case ID_TOMBSTONE_WOOD:
					this->addObject(new Tombstone(screenX - 4, screenY - SPRITE_SIZE, this, STATE_WOOD));
					break;
				case ID_TOMBSTONE_STONE:
					this->addObject(new Tombstone(screenX - 4, screenY - SPRITE_SIZE, this, STATE_STONE));
					break;
				case ID_TOMBSTONE_GOLDEN:
					this->addObject(new Tombstone(screenX - 4, screenY - SPRITE_SIZE, this, STATE_GOLDEN));
					break;
				case ID_ZOMBIE:
					this->addObject(new Zombie(screenX, screenY - SPRITE_SIZE, DIRECTION_LEFT, false));
					break;
				case ID_SUPER_ZOMBIE:
					this->addObject(new Zombie(screenX, screenY - 40, DIRECTION_LEFT, false, STATE_SUPER_NORMAL));
					break;
				}
			}
		}
	}

	void Level::processInput(u16 keysDown, u16 keysHeld) {
		if (this->frame % OBJECT_CLEAN_UP_FRAME_COUNT == 0) {
			this->objects->cleanUpObjects(this->player->getCenterX(), this->player->getCenterY());
		}

		this->player->doMovements(keysDown, keysHeld);
		this->objects->doActions(this->player->getCenterX(), this->player->getCenterY());
		this->objects->detectCollisionPlayer(this->player);
		this->objects->detectCollisionObjects();
	}

	u16 Level::getLevelStartX() {
		int16 startLevelX = this->player->getX() - Screen::WIDTH / 2;
		if (startLevelX < 0) {
			return 0;
		} else if (startLevelX > LEVEL_PIXEL_WIDTH - Screen::WIDTH) {
			return LEVEL_PIXEL_WIDTH - Screen::WIDTH;
		}
		return startLevelX;
	}

	u16 Level::getLevelStartY() {
		int16 startLevelY = this->player->getY() - Screen::HEIGHT / 2;
		if (startLevelY < 0) {
			return 0;
		} else if (startLevelY > LEVEL_PIXEL_HEIGHT - Screen::HEIGHT) {
			return LEVEL_PIXEL_HEIGHT - Screen::HEIGHT;
		}
		return startLevelY;
	}

	int16 Level::getScreenX(u16 x) {
		return x - this->getLevelStartX();
	}

	int16 Level::getScreenY(u16 y) {
		return y - this->getLevelStartY();
	}

	TileRegionId Level::getTileRegionId(u16 id) {
		switch (id) {
		case ID_GROUND:
			return REGION_GROUND;
		case ID_CEILING_ROUNDED_LEFT:
			return REGION_CEILING_ROUNDED_LEFT;
		case ID_CEILING_ROUNDED_RIGHT:
			return REGION_CEILING_ROUNDED_RIGHT;
		case ID_FLOOR:
			return REGION_FLOOR;
		case ID_FLOOR_ROUNDED_LEFT:
			return REGION_FLOOR_ROUNDED_LEFT;
		case ID_FLOOR_ROUNDED_RIGHT:
			return REGION_FLOOR_ROUNDED_RIGHT;
		case ID_FLOOR_SPIKES:
			return REGION_FLOOR_SPIKES;
		case ID_ROOF_SPIKES:
			return REGION_ROOF_SPIKES;
		case ID_WALL_SPIKES_LEFT:
			return REGION_WALL_SPIKES_LEFT;
		case ID_WALL_SPIKES_RIGHT:
			return REGION_WALL_SPIKES_RIGHT;
		case ID_SURFACE_LAVA:
			if (this->frame % (TILE_ANIMATION_FRAMES * 3) < 20) {
				return REGION_LAVA_SURFACE_1;
			} else if (this->frame % (TILE_ANIMATION_FRAMES * 3) < 40) {
				return REGION_LAVA_SURFACE_2;
			}
			return REGION_LAVA_SURFACE_3;
		case ID_LAVA:
			return REGION_LAVA;
		default:
			return REGION_NONE;
		}
		return REGION_NONE;
	}

	Player* Level::getPlayer() {
		return this->player;
	}

	bool Level::objectCapacityMaxed(){
		return this->objects->isMaxed();
	}

	/**
	 * @return bitmask of CollisionType elements so you can collide with multiple tiles
	 */
	u8 Level::detectLevelCollision(int16 x, int16 y, u8 width, u8 height){
		u8 collision = 0;

		if (x <= 0) {
			collision = collision | COLLIDE_EDGE;
		} else if (x + width >= LEVEL_PIXEL_WIDTH) {
			collision = collision | COLLIDE_EDGE;
		}

		if (y <= 0) {
			collision = collision | COLLIDE_EDGE;
		} else if (y + height >= LEVEL_PIXEL_HEIGHT) {
			collision = collision | COLLIDE_EDGE;
		}

		u16 levelX = x / SPRITE_SIZE;
		u16 levelY = y / SPRITE_SIZE;

		/*	We need to do collision detection for the tiles on 4 points
		 *	x,y && x + width,y && x, y + height && x + width, y + height
		 *	tiles above x and below y are irrelevant because x,y is the top left of any sprite. and x,y given are the
		 *	coordinates we are moving to.
		 *
		 *	Update:
		 *	This doesn't work if the sprite size is bigger than the level tilesize, because x and x + width could say no
		 *	collision takes place, but it actually does.
		 *	To fix this, we will now check on x + width / 2, y x + width / 2, y + height
		 */

		// Give everything a 4 pixel margin
		x += 2;
		y += 2;
		width -= 4;
		height -= 4;

		u16 tiles[8];
		// Up left tile
		tiles[0] = this->levelData[levelY * LEVEL_WIDTH  + levelX];
		// Up right tile
		tiles[1] = this->levelData[levelY * LEVEL_WIDTH + (x + width) / SPRITE_SIZE];
		// Middle left tile
		tiles[2] = this->levelData[(y + height / 2) / SPRITE_SIZE * LEVEL_WIDTH  + levelX];
		// Middle right tile
		tiles[3] = this->levelData[(y + height / 2) / SPRITE_SIZE * LEVEL_WIDTH + (x + width) / SPRITE_SIZE];
		// Down left tile
		tiles[4] = this->levelData[(y + height) / SPRITE_SIZE * LEVEL_WIDTH + levelX];
		// Down right tile
		tiles[5] = this->levelData[(y + height) / SPRITE_SIZE * LEVEL_WIDTH + (x + width) / SPRITE_SIZE];

		//	Middle bottom tile
		tiles[6] = this->levelData[(y + height) / SPRITE_SIZE * LEVEL_WIDTH + (x + width / 2) / SPRITE_SIZE];
		//	Middle top tile
		tiles[7] = this->levelData[levelY * LEVEL_WIDTH + (x + width / 2) / SPRITE_SIZE];

		for (u8 i = 0; i < 8; i++) {
			switch(tiles[i]) {
			case ID_GROUND:
			case ID_CEILING_ROUNDED_LEFT:
			case ID_CEILING_ROUNDED_RIGHT:
			case ID_FLOOR:
			case ID_FLOOR_ROUNDED_LEFT:
			case ID_FLOOR_ROUNDED_RIGHT:
				collision = collision | COLLIDE_TERRAIN;
				break;
			case ID_FLOOR_SPIKES:
			case ID_ROOF_SPIKES:
			case ID_WALL_SPIKES_LEFT:
			case ID_WALL_SPIKES_RIGHT:
				collision = collision | COLLIDE_SPIKES;
				break;
			case ID_LAVA:
			case ID_SURFACE_LAVA:
				collision = collision | COLLIDE_LAVA;
				break;
			}
		}

		if (this->objects->detectMovementCollisionObjects(x, y, width, height)) {
			collision = collision | COLLIDE_OBJECT;
		}

		return collision;
	}

	void Level::addObject(GameObject* object) {
		object->setLevel(this);
		this->objects->addObject(object, this->player->getCenterX(), this->player->getCenterY());
	}

	void Level::destroyObject(GameObject* object) {
		this->objects->destroyObject(object);
	}

	void Level::drawPlayer(Video* video) {
		this->player->draw(video);
	}

	void Level::drawObjects(Video* video){
		this->objects->drawObjects(video);
	}

	void Level::initializeLevelBuffer() {
		this->levelStartX = this->getLevelStartX();
		this->levelStartY = this->getLevelStartY();

		this->bufferStartX = 0;
		this->bufferStartY = 0;

		this->drawArea(this->bufferStartX, this->bufferStartY, this->levelStartX, this->levelStartY, Screen::WIDTH, Screen::HEIGHT);
	}

	void Level::drawLevel(Video* video) {
		int8 moveX = this->getLevelStartX() - this->levelStartX;
		int8 moveY = this->getLevelStartY() - this->levelStartY;

		if (moveX > 0) {
			// Draw an area with a size of moveX,Screen::HEIGHT at the right side of our buffer space
			this->drawArea(
				(this->bufferStartX + Screen::WIDTH) % Screen::WIDTH,
				this->bufferStartY,
				this->levelStartX + Screen::WIDTH,
				this->levelStartY,
				moveX,
				Screen::HEIGHT
			);
		} else if (moveX < 0) {
			// Draw an area with a size of moveX,Screen::HEIGHT at the left side of our buffer space
			this->drawArea(
				(this->bufferStartX + Screen::WIDTH + moveX) % Screen::WIDTH,
				this->bufferStartY,
				this->levelStartX + moveX,
				this->levelStartY,
				- moveX,
				Screen::HEIGHT
			);
		}

		// Prevent underrunning our startX by first adding the width and later subtracting it
		this->bufferStartX = (this->bufferStartX + Screen::WIDTH + moveX) % Screen::WIDTH;
		this->levelStartX = this->getLevelStartX();

		if (moveY > 0) {
			// Draw an area with a size of Screen::Width,moveY at the bottom side of our buffer space
			this->drawArea(
				this->bufferStartX,
				(this->bufferStartY + Screen::HEIGHT) % Screen::HEIGHT,
				this->levelStartX,
				this->levelStartY + Screen::HEIGHT,
				Screen::WIDTH,
				moveY
			);
		} else if (moveY < 0) {
			// Draw an area with a size of Screen::Width,moveY at the top side of our buffer space
			this->drawArea(
				this->bufferStartX,
				(this->bufferStartY + Screen::HEIGHT + moveY) % Screen::HEIGHT,
				this->levelStartX,
				this->levelStartY + moveY,
				Screen::WIDTH,
				- moveY
			);
		}

		// Prevent underrunning our startY by first adding the height and later subtracting it
		this->bufferStartY = (this->bufferStartY + Screen::HEIGHT + moveY) % Screen::HEIGHT;
		this->levelStartY = this->getLevelStartY();

		if (this->frame % TILE_ANIMATION_FRAMES == 0) {
			this->redrawAnimatedTiles();
		}

//		iprintf("# %d, %d # %d, %d\n", this->bufferStartX, this->bufferStartY, this->levelStartX, this->levelStartY);

		// Set the new buffer origin point
		video->getScreen(MAIN_SCREEN_BACKGROUND)->setBufferOrigin(this->bufferStartX, this->bufferStartY);

		this->frame++;
	}

	void Level::redrawAnimatedTiles() {
		u16 levelX, levelY, width, height;
		int32 bufferStartX, bufferStartY, levelStartX, levelStartY;
		u16 curTile;

		for (levelY = 0; levelY <= Screen::HEIGHT / SPRITE_SIZE; levelY++) {

			for (levelX = 0; levelX <= Screen::WIDTH / SPRITE_SIZE; levelX++) {
				curTile = this->levelData[(this->levelStartY / SPRITE_SIZE + levelY) * LEVEL_WIDTH + (this->levelStartX / SPRITE_SIZE + levelX)];

				if (curTile == ID_SURFACE_LAVA) {
					levelStartX = this->levelStartX + levelX * SPRITE_SIZE - (this->levelStartX % SPRITE_SIZE);
					levelStartY = this->levelStartY + levelY * SPRITE_SIZE - (this->levelStartY % SPRITE_SIZE);
					bufferStartX = this->bufferStartX + levelX * SPRITE_SIZE - (this->levelStartX % SPRITE_SIZE);
					bufferStartY = this->bufferStartY + levelY * SPRITE_SIZE - (this->levelStartY % SPRITE_SIZE);

					width = SPRITE_SIZE;
					height = SPRITE_SIZE;

					if (levelStartX < this->levelStartX) {
						width -= this->levelStartX - levelStartX;
						levelStartX = this->levelStartX;
						bufferStartX = this->bufferStartX;
					} else if (levelStartX + width > this->levelStartX + Screen::WIDTH) {
						width = this->levelStartX + Screen::WIDTH - levelStartX;
					}

					if (levelStartY < this->levelStartY) {
						height -= this->levelStartY - levelStartY;
						levelStartY = this->levelStartY;
						bufferStartY = this->bufferStartY;
					} else if (levelStartY + height > this->levelStartY + Screen::HEIGHT) {
						height = this->levelStartY + Screen::HEIGHT - levelStartY;
					}

					if (bufferStartX < 0) {
						bufferStartX = Screen::WIDTH + bufferStartX;
					}

					if (bufferStartY < 0) {
						bufferStartY = Screen::HEIGHT + bufferStartY;
					}

//					iprintf("%d, %d - %d, %d - %d, %d\n", bufferStartX, bufferStartY, levelStartX, levelStartY, width, height);
					this->drawArea(bufferStartX, bufferStartY, levelStartX, levelStartY, width, height);

				}
			}
		}
	}

	void Level::drawArea(u16 bufferStartX, u16 bufferStartY, u16 levelStartX, u16 levelStartY, u16 width, u16 height) {
		u16 levelX, levelY, bufferY, bufferX, actualBufferX, actualBufferY;
		u16 regionX, regionY, regionWidth, curTile;

		levelY = levelStartY;
		for (bufferY = bufferStartY; bufferY < bufferStartY + height; bufferY++) {
			actualBufferY = bufferY % Screen::HEIGHT;
			levelX = levelStartX;

			for (bufferX = bufferStartX; bufferX < bufferStartX + width; bufferX++) {
				actualBufferX = bufferX % Screen::WIDTH;

				curTile = this->levelData[(levelY / SPRITE_SIZE) * LEVEL_WIDTH + (levelX / SPRITE_SIZE)];
				curTile = this->getTileRegionId(curTile);

				regionX = this->spriteRegions[curTile]->getX() + (levelX % SPRITE_SIZE);
				regionY = this->spriteRegions[curTile]->getY() + (levelY % SPRITE_SIZE);

				if (actualBufferX + SPRITE_SIZE > bufferStartX + width) {
					regionWidth = bufferStartX + width - actualBufferX;
				} else {
					regionWidth = this->spriteRegions[curTile]->getWidth() - (levelX % SPRITE_SIZE);
				}
				this->levelBuffer[actualBufferY * Screen::WIDTH + actualBufferX] =
						this->tilesSprite->getPixelData()[regionY * this->tilesSprite->getWidth() + regionX];

				levelX++;
			}

			levelY++;
		}

	}
}
