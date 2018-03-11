#pragma once

#include "hge.h"
#include "hgecolor.h"
#include "hgesprite.h"
#include "hgevector.h"
#include "musicmanager.h"
#include "collisions.h"
#include "util.h"

namespace Spells
{

	//Global spells variables
	struct spellData
	{
		//Spell variables
		float energy;
		float delay;
	};

	hgeVector *MakeVector(point Destiny);

	/*============PROJECTILE SPELLS============*/
	struct Projectile
	{
		point		Coordinate;
		hgeSprite	*Sprite;
		float		collisionRadius;
		float		speed;
		float		xMove;
		float		yMove;
	};

	class ProjectileSpell
	{
	private:

	public:
		ProjectileSpell(){}
		virtual inline void Think(){}
		virtual inline void MakeTargets(){}
		virtual inline void Render(){}
	};

	class FireBall : public ProjectileSpell
	{
	};

	/*============WAVE SPELLS============*/
	class WaveSpell
	{
	public:
		WaveSpell(){}
		virtual inline void Think(){}
		virtual inline void MakeTargets(){}
		virtual inline void Render(){}
	};

	class FireWave : public WaveSpell
	{
	};

	/*============BOMB SPELLS============*/
	class BombSpell
	{
	public:
		BombSpell(){}
		virtual inline void Think(){}
		virtual inline void MakeTargets(){}
		virtual inline void Render(){}
	};

	class FireBomb : public BombSpell
	{
	};

	/*============SPECIAL SPELLS============*/
	class SpecialSpell
	{
	public:
		SpecialSpell(){}
		virtual inline void Think(){}
		virtual inline void MakeTargets(){}
		virtual inline void Render(){}
	};

	class FireDash : public SpecialSpell
	{
	};



	/*============SPELLS MANAGER============*/

	enum Elements
	{
		FIRE=0,
		EARTH,
		ENERGY,
		WATER
	};

	class SpellsManager
	{
	private:
		int	currentElement;
	public:
		SpellsManager() { currentElement=0; }
		~SpellsManager() {}
		void Think() {}
		void Render() {}
		inline const int CurrentElement() { return currentElement; }
	};

}