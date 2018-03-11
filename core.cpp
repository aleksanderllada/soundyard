#include "core.h"

using namespace core;

InstancesManager *GameCore::instance=NULL;

bool GameCore::Precache()
{
    HGE *hge;
    hge=hgeCreate(HGE_VERSION);
    if(!hge->Resource_AttachPack("Contents.zip"))
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			return false;
		}

	cursor=new MouseCursor();
    hge->Release();

    return true;
}

bool GameCore::Init()
{
    bool checkSucess;
    checkSucess = Precache();

    if(!checkSucess) return false;

	//Global classes/structures
    InputManager::Init();
	MusicManager::Init();
    MusicManager::SetMusic("C:/Music.mp3", 100);

    instance=new InstancesManager();
    instance->Init();

    return true;
}

bool GameCore::Think()
{
	cursor->Think();
    return instance->Think();
}

void GameCore::MakeTargets()
{
	instance->MakeTargets();
}

void GameCore::Render()
{
	cursor->Render();
    instance->Render();
}

GameCore::~GameCore()
{
    //Remove packs
    HGE *hge;
    hge=hgeCreate(HGE_VERSION);
    hge->Resource_RemoveAllPacks();
    hge->Release();

    //Shutdown everything
    InputManager::Shutdown();
    delete cursor;
}
