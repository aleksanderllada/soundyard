#pragma once

#ifndef GAMEINSTANCES_H_INCLUDED
#define GAMEINSTANCES_H_INCLUDED

#include "hgefont.h"
#include "hgegui.h"
#include "ai.h"
#include "hud.h"
#include "targetmap.h"
#include "collisions.h"
#include "backgrounds.h"
#include "mousecursor.h"
#include "menuitem.h"

namespace GameInstances
{

    using namespace ArtificialIntelligence;
    using namespace Maps;
    using namespace Collisions;
    using namespace Backgrounds;
	using namespace HUD;

	enum Signals
	{
		SIGNAL_TERMINATE=0,
		SIGNAL_CHANGEINSTANCE,
		SIGNAL_PAUSE
	};

	enum Instances
	{
		INSTANCE_MENU=0,
		INSTANCE_GRAPH,
		INSTANCE_INGAME
	};

	struct SIGNAL 
	{ 
		int signal; 
		int value;
		SIGNAL(int _signal, int _value) { signal=_signal; value=_value; }
		SIGNAL(int _signal, bool _value) { signal=_signal; value=(int)_value; }
		SIGNAL(){ signal=SIGNAL_TERMINATE; value=0; }
	};

    class GameInstance
    {
        //Public Methods
    public:
		virtual ~GameInstance() {}
        virtual inline void		GetScreenDisplacement() {}
        virtual inline void		Init() {}
        virtual inline SIGNAL	Think() {return SIGNAL(SIGNAL_TERMINATE, false);}
		virtual inline void		MakeTargets() {}
        virtual inline void		Render() {}
    };

	class InstancesManager
	{
	private:
		GameInstance *currentInstance;
		SIGNAL lastSignal;
	public:
		InstancesManager(){}
		void Init();
		bool Think();
		void MakeTargets();
		void Render();
	};

	/* MENU INSTANCE */

	class Menu : public GameInstance
	{
	private:
		HGE		*hge;
		hgeFont	*fnt;
		HEFFECT	snd;
		hgeGUI	*mainMenu;
	public:
		~Menu();
		void	Init();
		SIGNAL	Think();
		void	MakeTargets() {}
		void	Render();
	};

	/* GRAPH INSTANCE */

	class Graph : public GameInstance
	{
	public:
		void	Init() {}
		SIGNAL	Think() {}
		void	MakeTargets() {}
		void	Render() {}
	};

	/* IN-GAME INSTANCE */

	enum States
	{
		STATE_LOADING=0,
		STATE_ROLLING
	};

	enum LoadingSteps
	{
		LOAD_INIT=0,
		LOAD_MAP,
		LOAD_CHARACTER,
		LOAD_HUD,
		LOAD_MONSTERS,
		LOAD_COLLISIONS,
		LOAD_FINISH
	};

    class InGame : public GameInstance
    {
        //Private variables
    private:
		int				currentLoadStep;
		States			currentState;
        float			mousePositionX;
        float			mousePositionY;
        float			deltaValue;
        Character		*character;
        TargetMap		*map;
        CollisionMap	*mapCollisions;
		Monster			*monster;
        hgeFont			*fnt;
		HeadsUpDisplay	*playerHUD;
        HGE				*hge;

		//Private methods
	private:
		void LoadingState_Think();
		void LoadingState_MakeTargets() {}
		void LoadingState_Render();
		void RollingState_Think();
		void RollingState_MakeTargets();
		void RollingState_Render();
        //Public methods
    public:
        inline void GetScreenDisplacement(float *x, float *y)
        {
            *x=GameConfiguration::displacementX;
            *y=GameConfiguration::displacementY;
        }
        void	Init();
        SIGNAL	Think();
		void	MakeTargets();
        void	Render();
    };

}

#endif // GAMEINSTANCES_H_INCLUDED
