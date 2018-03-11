#include "ai.h"

using namespace ArtificialIntelligence;


void Character::SetDestination()
{
	if(InputManager::GetKeyState(HGEK_LBUTTON))
	{
        MouseCursor::GetMousePosition(&Data->goTo.x, &Data->goTo.y);
		Data->goTo.x-=GameConfiguration::displacementX;
		Data->goTo.y-=GameConfiguration::displacementY;
	}
}

void Character::Move()
{
	float storePosition;
    float storeDisplacement;
    bool canMoveX;
    bool canMoveY;
    circunference *collisionCircunference;

    //Store variables
    storeDisplacement=GameConfiguration::displacementX;
    storePosition=Data->position.x;
    //Move on X axis
    GameConfiguration::displacementX+=(float)(Data->speed*delta*xMultipler*1.5);
    Data->position.x=GameConfiguration::screenWidth/2 - GameConfiguration::displacementX;
	collisionCircunference=new circunference(point(Data->position.x, Data->position.y+10), 25);
    canMoveX=Collisions::CollisionMap::CheckCollision(collisionCircunference);
	delete collisionCircunference;

    if(!canMoveX)
    {
        GameConfiguration::displacementX=storeDisplacement;
        Data->position.x=storePosition;
    }

    //Store variables
    storeDisplacement=GameConfiguration::displacementY;
    storePosition=Data->position.y;
    //Move on Y axis
	if(xMultipler==0)
		GameConfiguration::displacementY+=(float)(Data->speed*delta*yMultipler*1.5);
	else
		GameConfiguration::displacementY+=(Data->speed*delta*yMultipler);
    Data->position.y=GameConfiguration::screenHeight/2 - GameConfiguration::displacementY;
    collisionCircunference=new circunference(point(Data->position.x, Data->position.y+10), 25);
    canMoveY=Collisions::CollisionMap::CheckCollision(collisionCircunference);
	delete collisionCircunference;

    if(!canMoveY)
    {
        GameConfiguration::displacementY=storeDisplacement;
        Data->position.y=storePosition;
    }
}

void Character::Think(float _delta)
{
    delta=_delta;

	SetEdgeColor();
	SetDestination();

	//If it has to move
	float distanceFromTarget=sqrt((pow(Data->position.x-Data->goTo.x, 2)+pow(Data->position.y-Data->goTo.y, 2)));
    if(distanceFromTarget>3) //If it isn't where it has to be (3 pixels off)
    {
        SetMovement();

        SetAnimDirectionBasedOnMousePos();

        Move();

        FinishMovementAndSetAnimation();

        //Set moving state
        Data->isMoving=true;
    }
    else
        Data->isMoving=false;

	spells->Think();

    Update();
}