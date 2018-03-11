#include "core.h"
#include "gameconfigurations.h"

using core::GameCore;

HGE *hge=0;
GameCore *game;

bool FrameFunc()
{
    if(hge->Input_GetKeyState(HGEK_ESCAPE))
        return true;

    return game->Think();
}

bool RenderFunc()
{
	game->MakeTargets();

    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0);

    game->Render();

    hge->Gfx_EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    GameConfiguration::Init();
    hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "RPG Logfile.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "RPG Music");
	hge->System_SetState(HGE_WINDOWED, false);
	hge->System_SetState(HGE_SCREENWIDTH, 1360);
	hge->System_SetState(HGE_SCREENHEIGHT, 768);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_ZBUFFER, true);
	hge->System_SetState(HGE_TEXTUREFILTER, true);

    bool checkReturnValue;

	if(hge->System_Initiate()) 
	{
	    game = new GameCore;
        checkReturnValue = game->Init();

        if(!checkReturnValue)
        {
            hge->System_Shutdown();
			hge->Release();
			return 0;
        }

        //Everything is ready!
		hge->System_Start();
	}

    delete game;

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
