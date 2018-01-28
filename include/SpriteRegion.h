/*
 * SpriteRegion.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef SPRITEREGION_H_
#define SPRITEREGION_H_

#include <nds.h>

namespace KIWF {
	class SpriteRegion {
	private:
		u16 x;
		u16 y;
		u16 width;
		u16 height;
	public:
		SpriteRegion(u16 x, u16 y, u16 width, u16 height);
		virtual ~SpriteRegion();

		u16 getX();
		u16 getY();
		u16 getWidth();
		u16 getHeight();

		void setX(u16 x);
		void setY(u16 y);
	};
}

#endif /* SPRITEREGION_H_ */
