/*
 * Mode.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef MODE_H_
#define MODE_H_

#include <nds.h>

#include "Video.h"
#include "SoundManager.h"
#include "Input.h"

namespace KIWF {

	class Mode {
	protected:
		Video* video;
		Input* input;
	public:
		Mode(Video* video, Input* input);
		virtual ~Mode();

		virtual void processInput() = 0;
	};
}

#endif /* MODE_H_ */
