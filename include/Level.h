/*
 * Level.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <nds.h>

#include "Video.h"
#include "Screen.h"
#include "SpriteManager.h"
#include "SpriteRegion.h"
#include "Player.h"
#include "GameObject.h"

#include "LEVEL_DATA.h"

namespace KIWF {
	//	Forward declaration for cyclic include
	class GameObjects;

	typedef enum {
		REGION_GROUND,
		REGION_CEILING_ROUNDED_LEFT,
		REGION_CEILING_ROUNDED_RIGHT,
		REGION_FLOOR,
		REGION_FLOOR_ROUNDED_LEFT,
		REGION_FLOOR_ROUNDED_RIGHT,
		REGION_FLOOR_SPIKES,
		REGION_ROOF_SPIKES,
		REGION_WALL_SPIKES_LEFT,
		REGION_WALL_SPIKES_RIGHT,
		REGION_LAVA,
		REGION_LAVA_SURFACE_1,
		REGION_LAVA_SURFACE_2,
		REGION_LAVA_SURFACE_3,
		REGION_NONE
	} TileRegionId;

	typedef enum {
		ID_PLAYER_SPAWN				= 0x6C1F,
		ID_PLAYER_SAVE				= 0x71BF,
		ID_NONE 					= 0x7FFF,
		ID_GROUND 					= 0x0000,
		ID_CEILING_ROUNDED_LEFT 	= 0x0006,
		ID_CEILING_ROUNDED_RIGHT	= 0x1800,
		ID_FLOOR 					= 0x18C6,
		ID_FLOOR_ROUNDED_LEFT		= 0x00C6,
		ID_FLOOR_ROUNDED_RIGHT		= 0x1886,
		ID_FLOOR_SPIKES 			= 0x7FE0,
		ID_ROOF_SPIKES				= 0x7FEF,
		ID_WALL_SPIKES_LEFT			= 0x3C04,
		ID_WALL_SPIKES_RIGHT		= 0x180F,
		ID_LAVA						= 0x3FBF,
		ID_SURFACE_LAVA				= 0x01BF,
		ID_WOODEN_BLOCK	 			= 0x00CF,
		ID_FALLING_BLOCK			= 0x3FF4,
		ID_SIGN 					= 0x037F,
		ID_FUEL_BARREL				= 0x13E0,
		ID_MUSHROOM 				= 0x001F,
		ID_HAMBURGER 				= 0x03F6,
		ID_CAKE						= 0x7DF4,
		ID_TOMBSTONE_WOOD 			= 0x7C09,
		ID_TOMBSTONE_STONE 			= 0x7E49,
		ID_TOMBSTONE_GOLDEN			= 0x7DA2,
		ID_ZOMBIE 					= 0x7C80,
		ID_SUPER_ZOMBIE 			= 0x6480
	} TileId;

	typedef enum {
		COLLIDE_NONE = 0,
		COLLIDE_EDGE = (1 << 7),
		COLLIDE_TERRAIN = (1 << 7),
		COLLIDE_SPIKES = (1 << 6),
		COLLIDE_LAVA = (1 << 5),
		COLLIDE_OBJECT = (1 << 4)
	} CollisionType;

	class Level {
	public:
		static const u8 DMA_CHANNEL = 2;

		static const u8 SPRITE_SIZE = 16;
		static const u8 LEVEL_NUM_SPRITE_REGIONS = 15;

		static const u16 OBJECT_CLEAN_UP_FRAME_COUNT = 100;

		static const u16 LEVEL_WIDTH = 400;
		static const u16 LEVEL_HEIGHT = 40;
		static const u16 LEVEL_PIXEL_WIDTH = LEVEL_WIDTH * SPRITE_SIZE;
		static const u16 LEVEL_PIXEL_HEIGHT = LEVEL_HEIGHT * SPRITE_SIZE;
		static const int32 LEVEL_NUM_PIXELS = LEVEL_WIDTH * LEVEL_HEIGHT;

		static const u8 TILE_ANIMATION_FRAMES = 30;

	private:
		//	Our actual level data in 1 pixel per tile.
		u16* levelData;
		//	Buffer for expanded tile level to be partially drawn to the screen
		u16* levelBuffer;
		//	Starting X coordinate of level data that is present in the levelBuffer
		u16 levelStartX;
		//	Starting Y coordinate of the level data present in the levelBuffer
		u16 levelStartY;
		//	X coordinate where the current LevelData starts in the buffer
		u16 bufferStartX;
		//	Y coordinate where the current levelData starts in the buffer
		u16 bufferStartY;

		Sprite* tilesSprite;
		SpriteRegion* spriteRegions[LEVEL_NUM_SPRITE_REGIONS];

		GameObjects* objects;
		Player* player;

		u16 playerSpawnX;
		u16 playerSpawnY;

		u16 frame;

	public:
		Level(Video* video);
		virtual ~Level();

		void instantiateLevelGameObjects();
		void createPlayer();

		u16 getLevelStartX();
		u16 getLevelStartY();
		int16 getScreenX(u16 levelX);
		int16 getScreenY(u16 levelY);
		TileRegionId getTileRegionId(u16 id);
		Player* getPlayer();

		void setPlayerSpawn(u16 x, u16 y);
		void respawnPlayer();

		void processInput(u16 keysDown, u16 keysHeld);
		void addObject(GameObject* o);
		void destroyObject(GameObject* o);
		void drawLevel(Video* video);
		void drawPlayer(Video* video);
		void drawObjects(Video* video);

		bool objectCapacityMaxed();
		u8 detectLevelCollision(int16 x, int16 y, u8 width, u8 height);

		void initializeLevelBuffer();
		void redrawAnimatedTiles();
		void drawArea(u16 bufferStartX, u16 bufferStartY, u16 levelStartX, u16 levelStartY, u16 width, u16 height);
		void drawSprite(int16 bufferX, int16 bufferY, Sprite* sprite, int8 regionX, int8 regionY, u8 regionWidth, u8 regionHeight);
	};
}

#include "GameObjects.h"

#endif /* LEVEL_H_ */
