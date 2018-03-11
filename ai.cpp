#include "ai.h"

using namespace ArtificialIntelligence;

AI::AI()
{
    hge=hgeCreate(HGE_VERSION);

	//spellsManager=new Spells();

	target=hge->Target_Create(60, 110, false);
	hge->Target_GetTexture(target, targetTexture);
	targetSprite=new hgeSprite(targetTexture, 0, 0, 60, 110);
	targetSprite->SetHotSpot(30, 55);
	targetSprite->SetBlendMode(BLEND_DEFAULT_Z);

    Data=new characterData;
    Data->maxHealth=1000;
    Data->currentHealth=500;
	Data->maxEnergy=50;
	Data->currentEnergy=25;
	GameConfiguration::displacementX=0; //Respawn Point
	GameConfiguration::displacementY=0; //Respawn Point
	Data->position.x=Data->goTo.x=GameConfiguration::screenWidth/2 - GameConfiguration::displacementX;
    Data->position.y=Data->goTo.y=GameConfiguration::screenHeight/2 - GameConfiguration::displacementY;
    Data->lastPosition.x=0;
    Data->lastPosition.y=0;
    Data->characterDirection=DIRECTION_DOWN;
    Data->currentDirection=DIRECTION_DOWN;
    Data->speed=150;
    Data->isMoving=false;
	Data->isPlayer=true;
    checkAnimation=false;

	spells=new Spells(&Data->currentEnergy, Data->maxEnergy);

    /*Prepare the animations of the character***********************************************/

    Data->characterTexture[0]=hge->Texture_Load("Character/Template_Shadow.png", 0, true);
    Data->characterTexture[1]=hge->Texture_Load("Character/Template_Edge1.png", 0, true);
    Data->characterTexture[2]=hge->Texture_Load("Character/Template_Edge2.png", 0, true);

    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        for(int animationDirection=0; animationDirection<8; animationDirection++)
        {
            Data->Animation[textureNumber][animationDirection]=new hgeAnimation(Data->characterTexture[textureNumber], 8, 12, 0, 110*(float)animationDirection, 60, 110);
            Data->Animation[textureNumber][animationDirection]->SetHotSpot(30, 55);
        }
    }

    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        Data->Animation[textureNumber][DIRECTION_LEFT]->SetMode(HGEANIM_REV | HGEANIM_LOOP);
        Data->Animation[textureNumber][DIRECTION_DOWN_RIGHT]->SetMode(HGEANIM_REV | HGEANIM_LOOP);
        Data->Animation[textureNumber][DIRECTION_UP_RIGHT]->SetMode(HGEANIM_REV | HGEANIM_LOOP);
    }


    //Play animations
    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        for(int animationDirection=0; animationDirection<8; animationDirection++)
        {
            Data->Animation[textureNumber][animationDirection]->Play();
        }
    }

    /*Prepare the 'standing' sprites of the character***********************************************/

    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        //Front
        Data->Standing[textureNumber][DIRECTION_DOWN]=new hgeSprite(Data->characterTexture[textureNumber], 0, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_DOWN]->SetHotSpot(30, 55);

        //Front left and right
        Data->Standing[textureNumber][DIRECTION_DOWN_LEFT]=new hgeSprite(Data->characterTexture[textureNumber], 60, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_DOWN_LEFT]->SetHotSpot(30, 55);

        Data->Standing[textureNumber][DIRECTION_DOWN_RIGHT]=new hgeSprite(Data->characterTexture[textureNumber], 420, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_DOWN_RIGHT]->SetHotSpot(30, 55);

        //Side
        Data->Standing[textureNumber][DIRECTION_LEFT]=new hgeSprite(Data->characterTexture[textureNumber], 120, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_LEFT]->SetHotSpot(30, 55);

        Data->Standing[textureNumber][DIRECTION_RIGHT]=new hgeSprite(Data->characterTexture[textureNumber], 360, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_RIGHT]->SetHotSpot(30, 55);

        //Back left and right
        Data->Standing[textureNumber][DIRECTION_UP_LEFT]=new hgeSprite(Data->characterTexture[textureNumber], 180, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_UP_LEFT]->SetHotSpot(30, 55);

        Data->Standing[textureNumber][DIRECTION_UP_RIGHT]=new hgeSprite(Data->characterTexture[textureNumber], 300, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_UP_RIGHT]->SetHotSpot(30, 55);

        //Back
        Data->Standing[textureNumber][DIRECTION_UP]=new hgeSprite(Data->characterTexture[textureNumber], 240, 881, 60, 110);
        Data->Standing[textureNumber][DIRECTION_UP]->SetHotSpot(30, 55);
    }
}

void AI::SetAnimationFrame(unsigned short int anim, unsigned short int frame)
{
    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        Data->Animation[textureNumber][anim]->SetFrame(frame);
    }
}

void AI::SetEdgeColor()
{
	for(int textureNumber=1; textureNumber<3; textureNumber++)
    {
        for(int animationDirection=0; animationDirection<8; animationDirection++)
        {
            Data->Standing[textureNumber][animationDirection]->SetColor(ARGB(MusicManager::GetMusicSpeed()*50, MusicManager::GetMusicSpeed()*50, MusicManager::GetMusicSpeed()*40, MusicManager::GetMusicSpeed()*25));
            Data->Animation[textureNumber][animationDirection]->SetColor(ARGB(MusicManager::GetMusicSpeed()*25, MusicManager::GetMusicSpeed()*25, MusicManager::GetMusicSpeed()*40, MusicManager::GetMusicSpeed()*50));
        }
    }
}

void AI::SetMovement()
{
	float xDistance=Data->position.x-Data->goTo.x;
	if(xDistance<0)
		xDistance*=(-1);

    //Check X axis movement
    if(xDistance>3)
    {
        if(Data->position.x<Data->goTo.x) //Check direction
            xMultipler=-1;
        else
            xMultipler=1;
    }
    else
        xMultipler=0;

	float yDistance=Data->position.y-Data->goTo.y;
	if(yDistance<0)
		yDistance*=(-1);

    //Check Y axis movement
    if(yDistance>3)
    {
        if(Data->position.y<Data->goTo.y) //Check direction
            yMultipler=-1;
        else
            yMultipler=1;
    }
        else
            yMultipler=0;
}

void AI::SetAnimDirectionBasedOnMousePos()
{
	if(InputManager::GetKeyState(HGEK_LBUTTON))
        {
            //Check move animation based on angle and do some maths for movement.
            //Create vector
            hgeVector *moveDirection;
            moveDirection=new hgeVector(Data->goTo.x-Data->position.x, Data->goTo.y-Data->position.y);

            //Calculate angle
            Data->angle=moveDirection->Angle();
            Data->angle*=(180/M_PI); //Convert to degrees

            delete moveDirection;

            /*Calculate player's direction
              *Here we have a problem, the angle returned by the function can be negative or positive,
              *and goes from -180º to 180º*/
            if(Data->angle>=15.0f && Data->angle<75.0f)
            {
                Data->characterDirection=DIRECTION_DOWN_RIGHT;
            }
            else if(Data->angle>=75.0f && Data->angle<105.0f)
            {
                Data->characterDirection=DIRECTION_DOWN;
                xMultipler=0;
            }
            else if(Data->angle>=105.0f && Data->angle<165.0f)
            {
                Data->characterDirection=DIRECTION_DOWN_LEFT;
            }
            else if(Data->angle>=165.0f || Data->angle<-165.0f)
            {
                Data->characterDirection=DIRECTION_LEFT;
                yMultipler=0;
            }
            else if(Data->angle>=-165.0f && Data->angle<-105.0f)
            {
                Data->characterDirection=DIRECTION_UP_LEFT;
            }
            else if(Data->angle>=-105.0f && Data->angle<-75.0f)
            {
                Data->characterDirection=DIRECTION_UP;
                xMultipler=0;
            }
            else if(Data->angle>=-75.0f && Data->angle<-15.0f)
            {
                Data->characterDirection=DIRECTION_UP_RIGHT;
            }
            else if(Data->angle>=-15.0f || Data->angle<15.0f)
            {
                Data->characterDirection=DIRECTION_RIGHT;
                yMultipler=0;
            }
            checkAnimation=true;
        }
}

void AI::FinishMovementAndSetAnimation()
{
	if(Data->position.x==Data->lastPosition.x && Data->position.y==Data->lastPosition.y)
    {
        Data->goTo.x=Data->position.x;
        Data->goTo.y=Data->position.y;
		//Non-player characters
		if(!Data->isPlayer)
			Data->isMoving=false;
    }
    else
    {
        Data->lastPosition.x=Data->position.x;
        Data->lastPosition.y=Data->position.y;

        if(!Data->isPlayer || !checkAnimation)
        {
            if(xMultipler==0 && yMultipler==-1)
                Data->characterDirection=DIRECTION_DOWN;
            else if(xMultipler==1 && yMultipler==0)
                Data->characterDirection=DIRECTION_LEFT;
            else if(xMultipler==-1 && yMultipler==0)
                Data->characterDirection=DIRECTION_RIGHT;
            else if(xMultipler==0 && yMultipler==1)
                Data->characterDirection=DIRECTION_UP;
            else if(xMultipler==1 && yMultipler==-1)
                Data->characterDirection=DIRECTION_DOWN_LEFT;
            else if(xMultipler==-1 && yMultipler==-1)
                Data->characterDirection=DIRECTION_DOWN_RIGHT;
            else if(xMultipler==1 && yMultipler==1)
                Data->characterDirection=DIRECTION_UP_LEFT;
            else if(xMultipler==-1 && yMultipler==1)
                Data->characterDirection=DIRECTION_UP_RIGHT;
			//Non-player characters
			if(!Data->isPlayer)
				Data->isMoving=true;
        }

        if(checkAnimation && Data->isPlayer)
        {
            if(Data->characterDirection==DIRECTION_DOWN || Data->characterDirection==DIRECTION_UP)
                Data->goTo.x=Data->position.x;
            else if(Data->characterDirection==DIRECTION_LEFT || Data->characterDirection==DIRECTION_RIGHT)
                Data->goTo.y=Data->position.y;

            checkAnimation=false;
        }
    }

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

void AI::Update()
{
    //Update only current animation
    for(int textureNumber=0; textureNumber<3; textureNumber++)
    {
        Data->Animation[textureNumber][Data->characterDirection]->Update(delta);
    }
}

void AI::MakeTargets()
{
	spells->MakeTargets();

	hge->Gfx_BeginScene(target);
	hge->Gfx_Clear(0);

	if(Data->isMoving)
    {
		Data->Animation[0][Data->characterDirection]->Render(30, 55);
		//spellsManager->RenderMask();
        for(int textureNumber=1; textureNumber<3; textureNumber++)
        {
            Data->Animation[textureNumber][Data->characterDirection]->Render(30, 55);
        }
    }
    else
    {
		Data->Standing[0][Data->characterDirection]->Render(30, 55);
		//spellsManager->RenderMask();
        for(int textureNumber=1; textureNumber<3; textureNumber++)
        {
            Data->Standing[textureNumber][Data->characterDirection]->Render(30, 55);
        }
    }

	hge->Gfx_EndScene();
}

void AI::Render()
{
	float z=1-(Data->position.y/10000);
	spells->Render(z, Data->position);
	targetSprite->SetZ(z);
	targetSprite->Render(Data->position.x, Data->position.y);
}
