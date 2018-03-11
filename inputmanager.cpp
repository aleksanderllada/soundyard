#include "inputmanager.h"

HGE *InputManager::hge;

bool InputManager::GetKeyState(int key)
{
    return hge->Input_GetKeyState(key);
}

bool InputManager::KeyUp(int key)
{
    return hge->Input_KeyUp(key);
}

bool InputManager::KeyDown(int key)
{
	return hge->Input_KeyDown(key);
}

point InputManager::GetMousePos()
{
	point mousePos;
	hge->Input_GetMousePos(&mousePos.x, &mousePos.y);
	return mousePos;
}

void InputManager::Init()
{
    hge=hgeCreate(HGE_VERSION);
}

void InputManager::Shutdown()
{
    hge->Release();
}
