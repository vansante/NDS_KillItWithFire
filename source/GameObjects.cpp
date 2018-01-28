/*
 * GameObjects.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */

#include "GameObjects.h"

namespace KIWF{

	GameObjects::GameObjects() {
		this->currentList = new GameObjectList();
		this->archiveList = new GameObjectList();
	}

	GameObjects::~GameObjects(){
		delete this->currentList;
		delete this->archiveList;
	}

	bool GameObjects::isMaxed() {
		return this->currentList->getCount() >= MAX_OBJECTS;
	}

	void GameObjects::doActions(u16 curX, u16 curY) {
		GameObjectItem* current = this->currentList->getFirst();
		GameObjectItem* next = NULL;

		while (current != NULL) {
			next = current->getNext();

			current->getObject()->doAction();

			current = next;
		}
	}

	void GameObjects::drawObjects(Video* video) {
		GameObjectItem* current = this->currentList->getFirst();

		while (current != NULL) {
			current->getObject()->draw(video);
			current = current->getNext();
		}
	}

	void GameObjects::addObject(GameObject* object, u16 curX, u16 curY) {
		if (this->calculateDistance(curX, curY, object->getX(), object->getY()) > object->getActiveRange()) {
			if (object->isCleanUpAllowed()) {
				delete object;
				return;
			} else {
				this->archiveList->addObject(object);
			}
		} else {
			this->currentList->addObjectPrioritized(object);
		}
	}

	void GameObjects::destroyObject(GameObject* object) {
		this->currentList->destroyObject(object);
	}

	void GameObjects::destroyAll() {
		this->currentList->destroyAll();
		this->archiveList->destroyAll();
	}

	u16 GameObjects::getObjectCount() {
		return this->currentList->getCount();
	}

	u16 GameObjects::calculateDistance(u16 x1, u16 y1, u16 x2, u16 y2) {
		return sqrt32((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}

	bool GameObjects::detectCollision(u16 x1, u16 y1, u16 width1, u16 height1, u16 x2, u16 y2, u16 width2, u16 height2) {
		if (y1 + height1 < y2) {
			return false;
		}
		if (y1 > y2 + height2) {
			return false;
		}

		if (x1 + width1 < x2) {
			return false;
		}
		if (x1 > x2 + width2) {
			return false;
		}
		return true;
	}

	bool GameObjects::detectMovementCollisionObjects(u16 x, u16 y, u8 width, u8 height) {
		GameObjectItem* current = this->currentList->getFirst();
		bool collide = false;

		while (current != NULL) {
			if (this->detectCollision(current->getObject()->getX(), current->getObject()->getY(), current->getObject()->getWidth(),
					current->getObject()->getHeight(), x, y, width, height)) {

				collide = current->getObject()->isImpassable();
				if (collide) {
					return collide;
				}
			}
			current = current->getNext();
		}
		return collide;
	}

	void GameObjects::detectCollisionObjects() {
		GameObjectItem* current = this->currentList->getFirst();
		GameObjectItem* collider = NULL;

		while (current != NULL) {
			collider = current->getNext();

			while (collider != NULL) {
				if (current == collider) {
					continue;
				}
				if (this->detectCollision(current->getObject()->getX(), current->getObject()->getY(), current->getObject()->getWidth(), current->getObject()->getHeight(),
							collider->getObject()->getX(), collider->getObject()->getY(), collider->getObject()->getWidth(), collider->getObject()->getHeight())) {

					current->getObject()->interact(collider->getObject());
					collider->getObject()->interact(current->getObject());
				}
				collider = collider->getNext();
			}
			current = current->getNext();
		}
	}

	void GameObjects::detectCollisionPlayer(Player* player) {
		GameObjectItem* current = this->currentList->getFirst();

		while (current != NULL) {
			if (this->detectCollision(current->getObject()->getX(), current->getObject()->getY(), current->getObject()->getWidth(), current->getObject()->getHeight(),
						player->getX(), player->getY(), player->getWidth(), player->getHeight())) {
				current->getObject()->interact(player);
			}
			current = current->getNext();
		}
	}

	void GameObjects::cleanUpObjects(u16 x, u16 y) {
		GameObjectItem* current = this->currentList->getFirst();
		GameObject* destroyObject = NULL;
		GameObject* archiveObject = NULL;

		while (current != NULL) {
			if (this->calculateDistance(x, y, current->getObject()->getX(), current->getObject()->getY()) > current->getObject()->getActiveRange()) {
				if (current->getObject()->isCleanUpAllowed()) {
					destroyObject = current->getObject();
				} else {
					archiveObject = current->getObject();
					this->archiveList->addObject(archiveObject);
				}
			}
			current = current->getNext();

			if (destroyObject != NULL) {
				this->currentList->destroyObject(destroyObject);
				destroyObject = NULL;
			} else if (archiveObject != NULL) {
				this->currentList->removeObject(archiveObject);
				archiveObject = NULL;
			}
		}

		current = this->archiveList->getFirst();

		while (current != NULL) {
			if (this->calculateDistance(x, y, current->getObject()->getX(), current->getObject()->getY()) <= current->getObject()->getActiveRange()) {
				archiveObject = current->getObject();
				this->currentList->addObjectPrioritized(archiveObject);

				//	Notify the object that it is entering the list of active items, so it might do stuff
				//	if it so desires. (only Tombstone does at this point)
				archiveObject->enterActiveList();
			}
			current = current->getNext();

			if (archiveObject != NULL) {
				this->archiveList->removeObject(archiveObject);
				archiveObject = NULL;
			}
		}
	}
}
