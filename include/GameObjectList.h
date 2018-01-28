/*
 * GameObjectList.h
 *
 *  Created on: 14 jun. 2011
 *      Author: Paul
 */

#ifndef GAMEOBJECTLIST_H_
#define GAMEOBJECTLIST_H_

#include "GameObject.h"

namespace KIWF {

	class GameObjectItem {
	private:
		GameObjectItem* next;
		GameObject* object;
	public:
		GameObjectItem();
		GameObjectItem(GameObject* object, GameObjectItem* next);
		virtual ~GameObjectItem();

		void setNext(GameObjectItem* object);
		GameObjectItem* getNext();

		void setObject(GameObject* object);
		GameObject* getObject();
	};

	class GameObjectList {
	private:
		GameObjectItem* first;
		u16 count;
	public:
		GameObjectList();
		virtual ~GameObjectList();

		void addObjectPrioritized(GameObject* object);
		void addObject(GameObject* object);
		void removeObject(GameObject* object);
		void destroyObject(GameObject* object);
		void destroyAll();

		u16 getCount();
		GameObjectItem* getFirst();

	};
}

#endif /* GAMEOBJECTLIST_H_ */
