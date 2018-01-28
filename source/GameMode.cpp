/*
 * GameMode.cpp
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#include "GameMode.h"

namespace KIWF {

	GameMode::~GameMode() {}

	void GameMode::processInput() {

		this->level->processInput(this->input->getKeysDown(), this->input->getKeysHeld());

		this->level->drawLevel(this->video);

		this->level->drawObjects(this->video);

		this->level->drawPlayer(this->video);

		this->gameUI->drawUI(this->video);
	}
}
