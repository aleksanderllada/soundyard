#pragma once

#include "hge.h"
#include "hgeanim.h"
#include "hgecolor.h"
#include "hgevector.h"
#include "spells.h"

namespace ElementsManager
{

	enum Elements
	{
		FIRE=0,
		EARTH,
		ENERGY,
		WATER
	};

	class ElementsManager
	{
	private:
		Elements	currentElement;
	public:
		void Init();
		void Think();
		inline const int CurrentElement() { return currentElement; }
	};

}