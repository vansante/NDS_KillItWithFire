/*
 * Sprite.h
 *
 *  Created on: 31 mei 2011
 *      Author: Paul
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <nds.h>

namespace KIWF {

	class Sprite {
	private:
		u16 width;
		u16 height;
		u16* pixelData;

		u16 tileWidth;
		u16 tileHeight;
	public:
		Sprite(u16 width, u16 height, u16* pixelData);
		Sprite(u16 width, u16 height, u16 tile_width, u16 tile_height, u16* pixelData);
		virtual ~Sprite();

		u16 getWidth();
		u16 getHeight();
		u16 getTileWidth();
		u16 getTileHeight();
		u16* getPixelData();
		u16 getPixelCount();
		u16 getByteSize();
	};
}

#endif /* SPRITE_H_ */
