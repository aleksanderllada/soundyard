#pragma once

#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgevector.h"
#include "hgefont.h"
#include "hgerect.h"
#include "collisions.h"
#include "inputmanager.h"
#include "mousecursor.h"
#include "gameconfigurations.h"
#include "musicmanager.h"
#include "spells.h"
#include "util.h"

namespace ArtificialIntelligence
{

	using namespace GeneralSpells;

    //Directions
    enum
    {
        DIRECTION_DOWN_LEFT=0,
        DIRECTION_DOWN,
        DIRECTION_DOWN_RIGHT,
        DIRECTION_LEFT,
        DIRECTION_RIGHT,
        DIRECTION_UP_LEFT,
        DIRECTION_UP,
        DIRECTION_UP_RIGHT
    };

    //Textures
    enum
    {
        TEXTURE_SHADOW=0,
        TEXTURE_EDGE1,
        TEXTURE_EDGE2
    };


    //Character data
    struct characterData
    {
        //Health
        float maxHealth;
        float currentHealth;

		//Energy
		int	maxEnergy;
		int currentEnergy;

        //Position
        point position;

        //Last position
        point lastPosition;

        //Position to go
        point goTo;

        //Speed
        int speed;

        //Is moving?
        bool isMoving;

		//Is player?
		bool isPlayer;

        //Angle
        float angle;

        //Texture
        HTEXTURE characterTexture[3]; //Shadow, Edge 1, Edge 2

        //Standing sprites
        hgeSprite *Standing[3][8]; //First array: Shadow, Edge 1, Edge 2 - Second array: Animation

        //Moving animations
        hgeAnimation    *Animation[3][8]; //First array: Texture - Second array: Animation

        //Character direction
        unsigned short int characterDirection;
        unsigned short int currentDirection; //Reset the animation whenever the character direction change.
    };

	class AI
	{
	private:
		HGE			*hge;

		//Target
		HTARGET		target;
		HTEXTURE	targetTexture;
		hgeSprite	*targetSprite;

	protected:
		//Data
		characterData   *Data;

		//Thinking variables
		int xMultipler;
		int yMultipler;
		float *displacementX;
		float *displacementY;

		//Spells manager
		Spells			*spells;

		//Timer variables
        float			delta;
        bool			checkAnimation;

		protected:
		//Thinking methods
        void SetAnimationFrame(unsigned short int anim, unsigned short int frame=0);
		void SetEdgeColor();
		void SetDestination() {}
		void SetMovement();
		void SetAnimDirectionBasedOnMousePos(); //This will be used only for the player
		void Move() {}
		void FinishMovementAndSetAnimation();
		void Update();

        //Public methods and constructors
    public:
        AI();
		
		//Basic Functions
		void MakeTargets();
        void Render();
		virtual void Think(){}

		//Necessary Functions
		inline point GetCoordinate() { return point(Data->position.x, Data->position.y); }
		//inline const int GetCurrentElement() { return spellsManager->CurrentElement(); }
		inline const float GetHealthPercent() { return (float)(Data->currentHealth/Data->maxHealth); }
	};

    class Character : public AI
    {
	private:
		void SetDestination();
		void Move();
	public:
		void Think(float _delta);
    };

	class Monster : public AI
	{
	private:
		point playerCoordinate;
		bool waitForMovement;
		float minimumDistanceFromPlayer;
		float maximumDistanceFromPlayer;
		float bestDistanceFromPlayer;
	private:
		void SetDestination();
		void Move();
	public:
		Monster()
		{
			waitForMovement=false;
			minimumDistanceFromPlayer=100;
			maximumDistanceFromPlayer=200;
			bestDistanceFromPlayer=150;
			AI();
			Data->speed=100;
			Data->isPlayer=false;
		}
		void Think(float _delta, point _playerCoordinate);
	};

}

#endif // CHARACTER_H_INCLUDED
