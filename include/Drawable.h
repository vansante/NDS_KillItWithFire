/*
 * Drawable.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <nds.h>
#include "Sprite.h"
#include "Video.h"

namespace KIWF {

	typedef enum {
		PRIORITY_1,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4
	} DrawPriority;

	typedef enum {
		DIRECTION_LEFT = 0,
		DIRECTION_RIGHT = 1,
		DIRECTION_UP = 2,
		DIRECTION_DOWN = 3,
		DIRECTION_UP_LEFT = 4,
		DIRECTION_DOWN_LEFT = 5,
		DIRECTION_UP_RIGHT = 6,
		DIRECTION_DOWN_RIGHT = 7
	} Direction;

	class Drawable {
	public:
		static const u16 NUM_PRIORITIES = 4;

		Drawable();
		virtual ~Drawable();

		u16 getX();
		u16 getY();
		u16 getWidth();
		u16 getHeight();
		DrawPriority getDrawPriority();
		Sprite* getSprite();

		virtual void destroy() = 0;
		virtual void bite(u16 damage) = 0;
		virtual void burn(u16 damage) = 0;
		virtual void upgrade() = 0;
		virtual void fuel(u16 amount) = 0;
		virtual void heal(u16 amount) = 0;
		virtual void cake() = 0;

		virtual void draw(Video* video) = 0;

	protected:
		Sprite* sprite;
		u16 x;
		u16 y;
		DrawPriority drawPriority;
	};

}

#endif /* DRAWABLE_H_ */
