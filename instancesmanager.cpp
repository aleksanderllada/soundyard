#include "gameinstances.h"

using GameInstances::InstancesManager;

void InstancesManager::Init()
{
	currentInstance=new Menu();
	currentInstance->Init();
}

bool InstancesManager::Think()
{
	lastSignal=currentInstance->Think();

	if(lastSignal.signal==SIGNAL_TERMINATE && lastSignal.value==1)
		return true;

	if(lastSignal.signal==SIGNAL_CHANGEINSTANCE)
	{
		delete currentInstance;
		currentInstance=new InGame();
		currentInstance->Init();
	}

	return false;
}

void InstancesManager::MakeTargets()
{
	currentInstance->MakeTargets();
}

void InstancesManager::Render()
{
	currentInstance->Render();
}