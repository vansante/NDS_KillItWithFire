/*
 * object.h
 *
 *  Created on: Jun 3, 2011
 *      Author: aeterno
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Drawable.h"
#include "constants.h"

namespace KIWF {
	//	Forward declaration
	class Level;

	class GameObject : public Drawable {
	protected:
		u16 activeRange;
		bool allowCleanUp;
		bool impassable;

		Level* level;
	public:
		virtual void interact(Drawable* drawable) = 0;
		virtual void doAction() = 0;
		virtual void enterActiveList() = 0;

		void setLevel(Level* level);

		u16 getActiveRange();
		bool isCleanUpAllowed();
		bool isImpassable();
	};

}

#include "Level.h"

#endif /* OBJECT_H_ */
