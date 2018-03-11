#pragma once

#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include "hge.h"
#include "util.h"

class InputManager
{
private:
    static HGE *hge;
public:
    static void		Init();
    static void		Shutdown();
    static bool		GetKeyState(int key);
    static bool		KeyUp(int key);
	static bool		KeyDown(int key);
	static point	GetMousePos();
};

#endif // INPUTMANAGER_H_INCLUDED
