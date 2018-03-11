#pragma once

#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "hge.h"
#include "hgefont.h"
#include "mousecursor.h"
#include "musicmanager.h"
#include "gameinstances.h"

namespace core
{

    using namespace GameInstances;

    class GameCore
    {
        //Private variables
    private:
        static InstancesManager	*instance;
        MouseCursor *cursor;
        float mouseX; //Includes displacement
        float mouseY;

        //Public constructors/destructors
    public:
        ~GameCore();

        //Public methods
    public:
        //Initialization methods
        bool Precache();
        bool Init();
        //Thinking methods
        bool Think();
        //Rendering methods
		void MakeTargets();
        void Render();
    };

}

#endif // CORE_H_INCLUDED
