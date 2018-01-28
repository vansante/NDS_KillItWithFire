/*
 * Sign.cpp
 *
 *  Created on: 7 jun. 2011
 *      Author: Paul
 */

#include "Sign.h"

namespace KIWF {

	Sign::Sign(u16 x, u16 y) {
		this->x = x;
		this->y = y;
		this->activeRange = 350;
		this->allowCleanUp = false;
		this->drawPriority = PRIORITY_4;
		this->impassable = false;
		this->isShowing = false;

		this->setSignText();

		this->sprite = SpriteManager::getInstance().get(SIGN_SPRITE);
	}

	Sign::~Sign() {}

	void Sign::setSignText() {
		if (this->x == 11 && this->y == 114) {
			this->signText = "Hi, this is a sign.\n\nYou can read it by standing in \nfront of it.\n \nYou move by pressing the arrow keys\n \nTo fly with your rockets, press A.\n \nTo shoot a fireball, press B.\n\nBeware though, both of these use\nfuel.";
		} else if (this->x == 187 && this->y == 114) {
			this->signText = "See that cake over there?\n\nIt is a li- I mean, your objective!\n \nYou must get it! Mmmh, cake!";
		} else if (this->x == 251 && this->y == 114) {
			this->signText = "These are spikes.\n \nBest not to touch them if you\nwant to stay healthy.";
		} else if (this->x == 379 && this->y == 114) {
			this->signText = "This is lava.\n \nLava is hot and firey.\n \nIt will burn.\n \nYou will hurt.";
		} else if (this->x == 491 && this->y == 114) {
			this->signText = "This is a tombstone.\n \nIt will spawn zombies.\n \nZombies want to eat your brain.\n \nThis is bad.\n \nYou had better burn the zombies\nand their tombstones.";
		} else if (this->x == 667 && this->y == 114) {
			this->signText = "Here are some useful items.\n\nThe hamburger will restore your\nhealth (the hearts in the corner).\n\nThe fuel barrel will restore your\nfuel (the bar in the other corner).\n\nThe mushroom will make you shoot a\npowerful fireball. Dont let the\nzombies eat it though...";
		} else if (this->x == 1307 && this->y == 50) {
			this->signText = "You should probably run fast\nthis next part..";
		} else if (this->x == 2107 && this->y == 162) {
			this->signText = "Stone does not burn..";
		} else if (this->x == 2539 && this->y == 130) {
			this->signText = "This is a save point.\n\nIf you die, you will respawn here.";
		} else if (this->x == 2651 && this->y == 18) {
			this->signText = "Have a nice flight!";
		} else if (this->x == 3531 && this->y == 130) {
			this->signText = "Didnt I tell you about mushrooms\nand zombies?";
		} else if (this->x == 4283 && this->y == 162) {
			this->signText = "These crates do not seem\nvery fireproof.. Perhaps you should\nfire them up?";
		} else if (this->x == 4891 && this->y == 50) {
			this->signText = "Watch out! .. for stuff";
		} else if (this->x == 6107 && this->y == 594) {
			this->signText = "Golden tombstones really are\na bitch..\n\nMaybe you have some use for\nthis mushroom..";
		} else if (this->x == 107 && this->y == 210) {
			this->signText = "The icing on this cake was made\npossible by:\n\nPaul van Santen\n\n&\n\nRick Woelders";
		} else {
			this->signText = "Ohnoes! This sign appears to be\nbroken!";
			iprintf("Sign coordinates (%d, %d)\n", this->x, this->y);
		}
	}

	void Sign::enterActiveList(){};

	void Sign::interact(Drawable* drawable) {}

	void Sign::destroy() {}

	void Sign::bite(u16 damage) {}

	void Sign::burn(u16 damage) {}

	void Sign::upgrade() {}

	void Sign::fuel(u16 amount) {}

	void Sign::heal(u16 amount) {}

	void Sign::cake() {}

	void Sign::doAction() {}

	void Sign::draw(Video* video) {
		video->drawSprite(MAIN_SCREEN_FOREGROUND, true, this->level->getScreenX(this->x), this->level->getScreenY(this->y), this->sprite);
		Player* player = this->level->getPlayer();

		u16 x = this->x + this->sprite->getWidth() / 2;
		u16 y = this->y + this->sprite->getHeight() / 2;
		u16 playerX = player->getCenterX();
		u16 playerY = player->getCenterY();

		u16 distance = sqrt32((playerX - x) * (playerX - x) + (playerY - y) * (playerY - y));

		// Only show text if the player is standing in front of the sign
		if (!this->isShowing && distance <= ACTIVATE_DISTANCE) {
			#ifdef DEBUG_MODE
				iprintf(this->signText);
			#else
				video->fillBackground(TOUCH_SCREEN_FOREGROUND, TEXT_BACKGROUND_COLOR);
				video->drawString(TOUCH_SCREEN_FOREGROUND, this->signText, 4, 4, 248, 184);
				video->swapBuffer(TOUCH_SCREEN_FOREGROUND);
			#endif
			this->isShowing = true;
		} else if (this->isShowing && distance < ACTIVATE_DISTANCE * 2 && distance > ACTIVATE_DISTANCE) {
			#ifndef DEBUG_MODE
				video->clearScreen(TOUCH_SCREEN_FOREGROUND);
				video->swapBuffer(TOUCH_SCREEN_FOREGROUND);
			#endif
			this->isShowing = false;
		}
	}
}
