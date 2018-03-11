#pragma once

#include "ai.h"
#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "spells.h"

namespace HUD
{

	class HeadsUpDisplay
	{
	private:
		//HGE Pointer
		HGE				*hge;

		//Interface elements
		HTEXTURE		hudTexture;
		HTEXTURE		targetTexture;
		HTARGET			hudTarget;
		HTEXTURE		energyTexture;
		hgeAnimation	*energyAnimation;
		hgeSprite		*targetSprite;
		hgeSprite		*hudSprite;
		hgeSprite		*hudHP;
		hgeSprite		*hudEnergy;
	public:
		HeadsUpDisplay();
		~HeadsUpDisplay();
		void Think(int _currentElement);
		void MakeTargets(float healthPercent);
		void Render(float displacementX, float displacementY);
	};

}