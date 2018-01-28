/*
 * GameObjectList.cpp
 *
 *  Created on: 14 jun. 2011
 *      Author: Paul
 */

#include "GameObjectList.h"

namespace KIWF {

	GameObjectItem::GameObjectItem() {
		this->object = NULL;
		this->next = NULL;
	}

	GameObjectItem::GameObjectItem(GameObject* object, GameObjectItem* next) {
		this->object = object;
		this->next = next;
	}

	GameObjectItem::~GameObjectItem() {}

	void GameObjectItem::setNext(GameObjectItem* next) {
		this->next = next;
	}

	GameObjectItem* GameObjectItem::getNext() {
		return this->next;
	}

	void GameObjectItem::setObject(GameObject* object) {
		this->object = object;
	}

	GameObject* GameObjectItem::getObject() {
		return this->object;
	}

	GameObjectList::GameObjectList() {
		this->count = 0;
		this->first = NULL;
	}

	GameObjectList::~GameObjectList() {
		this->destroyAll();
	}

	void GameObjectList::addObjectPrioritized(GameObject* object) {
		if (this->first == NULL) {
			this->first = new GameObjectItem(object, this->first);
		} else {
			GameObjectItem* current = this->first;
			u8 priority = object->getDrawPriority();

			while (true) {
				if (current->getNext() != NULL && current->getObject()->getDrawPriority() > priority) {
					current = current->getNext();
				} else {
					break;
				}
			}
			current->setNext(new GameObjectItem(object, current->getNext()));
		}
		this->count++;
	}

	void GameObjectList::addObject(GameObject* object) {
		this->first = new GameObjectItem(object, this->first);
		this->count++;
	}

	void GameObjectList::removeObject(GameObject* object) {
		if (this->first->getObject() == object) {
			GameObjectItem* item = this->first;
			this->first = this->first->getNext();
			delete item;
		} else {
			GameObjectItem* current = this->first;
			GameObjectItem* previous = NULL;

			while (current != NULL) {
				if (current->getObject() == object) {
					previous->setNext(current->getNext());
					break;
				}
				previous = current;
				current = current->getNext();
			}
			delete current;
		}
		this->count--;
	}
	void GameObjectList::destroyObject(GameObject* object) {
		this->removeObject(object);
		delete object;
	}

	void GameObjectList::destroyAll() {
		// Kill everything in this list HARR!
		GameObjectItem* current = this->first;
		GameObjectItem* item;
		while (current != NULL) {
			item = current;
			current = current->getNext();

			delete item->getObject();
			delete item;
		}
		this->first = NULL;
		this->count = 0;
	}

	u16 GameObjectList::getCount() {
		return this->count;
	}

	GameObjectItem* GameObjectList::getFirst() {
		return this->first;
	}
}
