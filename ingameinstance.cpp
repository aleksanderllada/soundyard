#include "gameinstances.h"

using namespace GameInstances;

void InGame::Init()
{
	currentLoadStep=LOAD_INIT;
	currentState=STATE_LOADING;

	fnt=new hgeFont("gamefont.fnt");

    hge=hgeCreate(HGE_VERSION);
}

void InGame::MakeTargets()
{
	switch(currentState)
	{
	case STATE_LOADING:
		LoadingState_MakeTargets();
		break;
	case STATE_ROLLING:
		RollingState_MakeTargets();
		break;
	}
}

void InGame::Render()
{
	switch(currentState)
	{
	case STATE_LOADING:
		LoadingState_Render();
		break;
	case STATE_ROLLING:
		RollingState_Render();
		break;
	}
}

SIGNAL InGame::Think()
{
	switch(currentState)
	{
	case STATE_LOADING:
		LoadingState_Think();
		break;
	case STATE_ROLLING:
		RollingState_Think();
		break;
	}

	return SIGNAL(SIGNAL_TERMINATE, false);
}

void InGame::LoadingState_Render()
{
	switch(currentLoadStep)
	{
	case LOAD_INIT:
		break;
	case LOAD_MAP:
		fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "Loading map...");
		break;
	case LOAD_CHARACTER:
		fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "Loading character...");
		break;
	case LOAD_HUD:
		fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "Loading HUD...");
		break;
	case LOAD_MONSTERS:
		fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "Loading monsters...");
		break;
	case LOAD_COLLISIONS:
		fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "Loading collisions...");
		break;
	case LOAD_FINISH:
		break;
	}
}

void InGame::LoadingState_Think()
{
	switch(currentLoadStep)
	{
	case LOAD_INIT:
		break;
	case LOAD_MAP:
		map=new Glacier();
		break;
	case LOAD_CHARACTER:
		character=new Character();
		break;
	case LOAD_HUD:
		playerHUD=new HeadsUpDisplay();
		break;
	case LOAD_MONSTERS:
		monster=new Monster();
		break;
	case LOAD_COLLISIONS:
		mapCollisions=new CollisionMap(map->GetMatrix());
		break;
	case LOAD_FINISH:
		currentState=STATE_ROLLING; //Change State
		MusicManager::Play();
		return;
	}
	currentLoadStep++;
}

void InGame::RollingState_MakeTargets()
{
	playerHUD->MakeTargets(character->GetHealthPercent());
	character->MakeTargets();
	monster->MakeTargets();
}

void InGame::RollingState_Render()
{
	//Set screen transformation
    hge->Gfx_SetTransform(0, 0, GameConfiguration::displacementX, GameConfiguration::displacementY, 0, 1, 1);

    //Render everything
    map->Render();

    character->Render();
	monster->Render();
	playerHUD->Render(GameConfiguration::displacementX, GameConfiguration::displacementY);
	fnt->printf(-GameConfiguration::displacementX+5, -GameConfiguration::displacementY+5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d\nSpeed:%.3f", hge->Timer_GetDelta(), hge->Timer_GetFPS(), MusicManager::GetMusicSpeed());
}

void InGame::RollingState_Think()
{
	deltaValue=hge->Timer_GetDelta();
    //Make everything think
	character->Think(deltaValue);
    map->Think(deltaValue);
	monster->Think(deltaValue, character->GetCoordinate());

	playerHUD->Think(0);
}