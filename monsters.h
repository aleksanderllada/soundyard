//#pragma once

/* The monsters work exactly as the player, but they take their own decisions on where they have to go */
/*
#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED

#include "hge.h"
#include "hgeanim.h"
#include "hgevector.h"
#include "gameconfigurations.h"
#include "musicmanager.h"
#include "collisions.h"
#include "util.h"

namespace Monsters
{
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

    struct monsterData
    {
        //Health
        int maxHealth;
        int currentHealth;

        //Position
        float xPosition;
        float yPosition;

		//Distance from player
		float minimumDistanceFromPlayer;
		float maximumDistanceFromPlayer;
		float bestDistanceFromPlayer;

        //Last position
        float lastPositionX;
        float lastPositionY;

        //Position to go
        float goToX;
        float goToY;

        //Speed
        int speed;

        //Is moving?
        bool isMoving;
		
		//Thinking variables
		bool waitForMovement;

        //Angle
        float angle;

        //Texture
        HTEXTURE monsterTexture[4]; //Shadow, Edge 1, Edge 2, Edge 3

        //Standing sprites
        hgeSprite *Standing[3][8]; //First array: Texture - Second array: Animation

        //Moving animations
        hgeAnimation    *Animation[3][8]; //First array: Texture - Second array: Animation

        //Character direction
        unsigned short int monsterDirection;
        unsigned short int currentDirection; //Reset the animation whenever the character direction change.
    };

    class Monster
    {
	private:
        monsterData *Data;

		//Timer variable
        float   deltaValue;
        bool    checkAnimation;

	private:
		void Update();
        void SetAnimationFrame(unsigned short int anim, unsigned short int frame=0);

    public:
        Monster();

		point GetCoordinate() { return point(Data->xPosition, Data->yPosition); }
        void Think(float delta, point playerCoordinate);
        void Render();
    };

}

#endif // MONSTERS_H_INCLUDED
*/