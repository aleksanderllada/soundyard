#include "ai.h"

using namespace ArtificialIntelligence;

void Monster::SetDestination()
{
	if(Data->isMoving==false)
		waitForMovement=false;
	
	//Wait until finish the movement (if it has to)
	if(waitForMovement==false)
	{
		if(DistanceBetweenTwoPoints(point(Data->position.x, Data->position.y), playerCoordinate)>maximumDistanceFromPlayer ||
		   DistanceBetweenTwoPoints(point(Data->position.x, Data->position.y), playerCoordinate)<minimumDistanceFromPlayer)
		{
			hgeVector *angleVector=new hgeVector((Data->position.x-playerCoordinate.x), (Data->position.y-playerCoordinate.y));
			float angle=angleVector->Angle();
			delete angleVector;

			hgeVector *newAngle=new hgeVector(bestDistanceFromPlayer, 0);
			newAngle->Rotate(angle);
			circunference *testCircunference;
			bool testCollision;
			while(true)
			{
				testCircunference=new circunference(point(newAngle->x+playerCoordinate.x, newAngle->y+playerCoordinate.y), 25);
				testCollision=Collisions::CollisionMap::CheckCollision(testCircunference);
				if(testCollision)
				{
					Data->goTo.x=newAngle->x+playerCoordinate.x;
					Data->goTo.y=newAngle->y+playerCoordinate.y;
					break;
				}
				else
					waitForMovement=true;
				angle+=(M_PI/90);
				newAngle->Rotate(angle);
			}
		}
	}
}

void Monster::Move()
{
	float storePosition;
    bool canMoveX;
    bool canMoveY;
    circunference *collisionCircunference;

    //Store variables
    storePosition=Data->position.x;
    //Move on X axis
    Data->position.x+=(float)(-xMultipler*Data->speed*delta*1.5);
	collisionCircunference=new circunference(point(Data->position.x, Data->position.y+10), 25);
    canMoveX=Collisions::CollisionMap::CheckCollision(collisionCircunference);
	delete collisionCircunference;

    if(!canMoveX)
    {
        Data->position.x=storePosition;
    }

    //Store variables
    storePosition=Data->position.y;
    //Move on Y axis
	if(xMultipler==0)
		Data->position.y+=(float)(-yMultipler*Data->speed*delta*1.5);
	else
		Data->position.y+=(-yMultipler*Data->speed*delta);
    collisionCircunference=new circunference(point(Data->position.x, Data->position.y+10), 25);
    canMoveY=Collisions::CollisionMap::CheckCollision(collisionCircunference);
	delete collisionCircunference;

    if(!canMoveY)
    {
        Data->position.y=storePosition;
    }
}

void Monster::Think(float _delta, point _playerCoordinate)
{
	delta=_delta;
	playerCoordinate=_playerCoordinate;

	//spellsManager->Think(delta);

	SetEdgeColor();

	SetDestination();

	//If it has to move
	float distanceFromTarget=sqrt((pow(Data->position.x-Data->goTo.x, 2)+pow(Data->position.y-Data->goTo.y, 2)));
    if(distanceFromTarget>3) //If it isn't where it has to be (3 pixels off)
    {
        SetMovement();

        Move();

        FinishMovementAndSetAnimation();

        if(Data->isMoving==false)
        {
			SetAnimationFrame(Data->characterDirection);
        }
        else if(Data->currentDirection!=Data->characterDirection)
        {
            SetAnimationFrame(Data->characterDirection, Data->Animation[0][Data->currentDirection]->GetFrame());
            Data->currentDirection=Data->characterDirection;
        }
    }
    else
        Data->isMoving=false;

	spells->Think();

    Update();
}