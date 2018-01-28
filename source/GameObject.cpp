/*
 * object.h
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */

#include "GameObject.h"

namespace KIWF {

	void GameObject::setLevel(Level* level){
		this->level = level;
	}

	u16 GameObject::getActiveRange() {
		return this->activeRange;
	}

	bool GameObject::isCleanUpAllowed() {
		return this->allowCleanUp;
	}

	bool GameObject::isImpassable(){
		return this->impassable;
	}
}
