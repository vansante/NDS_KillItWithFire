/*
 * GameObjects.h
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */

#ifndef GAMEOBJECTS_H_
#define GAMEOBJECTS_H_

#include "constants.h"

#include "Video.h"
#include "GameObject.h"
#include "Player.h"

namespace KIWF {

//	Forward declaration for cyclic include
	class Level;
	class GameObjectList;

	class GameObjects {
	public:
		static const u16 MAX_OBJECTS = 75;

	private:
		GameObjectList* currentList;
		GameObjectList* archiveList;

	public:
		GameObjects();
		virtual ~GameObjects();
		void drawObjects(Video* video);
		void doActions(u16 curX, u16 curY);
		void addObject(GameObject* object, u16 curX, u16 curY);
		void destroyObject(GameObject* object);
		void destroyAll();

		u16 getObjectCount();
		bool isMaxed();
		u16 calculateDistance(u16 x1, u16 y1, u16 x2, u16 y2);

		bool detectCollision(u16 x1, u16 y1, u16 width1, u16 height1, u16 x2, u16 y2, u16 width2, u16 height2);
		void detectCollisionObjects();
		void detectCollisionPlayer(Player* player);
		bool detectMovementCollisionObjects(u16 x, u16 y,u8 width, u8 height);

		void cleanUpObjects(u16 x, u16 y);
	};

}  // namespace KIWF

#include "Level.h"
#include "GameObjectList.h"
#endif /* GAMEOBJECTS_H_ */
