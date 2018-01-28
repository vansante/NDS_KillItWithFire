/*
 * Cake.cpp
 *
 *  Created on: Jun 8, 2011
 *      Author: aeterno
 */

#include "Cake.h"

namespace KIWF{

	Cake::Cake(u16 x, u16 y){
		this->x = x;
		this->y = y;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;
		this->activeRange = 350;
		this->allowCleanUp = false;

		this->sprite = SpriteManager::getInstance().get(CAKE_SPRITE);
	}

	Cake::~Cake(){}

	void Cake::enterActiveList(){};

	void Cake::interact(Drawable* drawable){
		drawable->cake();
	}

	void Cake::destroy(){}

	void Cake::bite(u16 damage){}

	void Cake::burn(u16 damage){}

	void Cake::upgrade(){}

	void Cake::fuel(u16 amount){}

    void Cake::heal(u16 amount){}

    void Cake::cake() {}

	void Cake::doAction(){

	}

	void Cake::draw(Video* video){
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
	}
};
