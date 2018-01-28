/*
 * Input.h
 *
 *  Created on: 30 mei 2011
 *      Author: Paul
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <nds.h>

namespace KIWF {

	class Input {
	private:
		u16 _keysDown, _keysUp, _keysHeld;
		touchPosition* _touchPos;
	public:
		Input();
		virtual ~Input();

		void fetchInput();
		u16 getKeysDown();
		u16 getKeysUp();
		u16 getKeysHeld();
		u16 getTouchX();
		u16 getTouchY();
	};
}

#endif /* INPUT_H_ */
