#pragma once

#include "hge.h"
#include "hgecolor.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgevector.h"
#include "musicmanager.h"
#include "collisions.h"
#include "util.h"
#include <time.h>
#include <stdlib.h>

namespace GeneralSpells
{

	struct Particle
	{
		point position;
		short int xMultipler;
		short int yMultipler;
	};

	class Spells
	{
	private:
		HGE				*hge;

		//Particle
		HTEXTURE		particleTexture;
		hgeSprite		*particleSprite;
		DWORD			particleColor;
		Particle		*particles;

		//Particle's movement
		float			xDisplacement;
		float			yDisplacement;

		//Character energy
		int				*currentEnergy;

		//Front and back targets
		HTEXTURE		frontTargetTexture;
		HTARGET			frontTarget;
		HTEXTURE		backTargetTexture;
		HTARGET			backTarget;
		hgeSprite		*frontTargetSprite;
		hgeSprite		*backTargetSprite;
	public:
		Spells(int *_currentEnergy, int maxEnergy);
		~Spells() {}
		void Think();
		void MakeTargets();
		void Render(float z, point coordinate);
	};

}