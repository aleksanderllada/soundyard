#include "gameinstances.h"

using namespace GameInstances;

void Menu::Init()
{
	hge=hgeCreate(HGE_VERSION);
	mainMenu=new hgeGUI();

	fnt=new hgeFont("gamefont.fnt");
	fnt->SetBlendMode(BLEND_DEFAULT_Z);
	fnt->SetZ(0.1f);
	snd=hge->Effect_Load("menu.wav");

	mainMenu->AddCtrl(new hgeGUIMenuItem(1, fnt, snd, 400, 200, 0.1f, "Play"));
	mainMenu->AddCtrl(new hgeGUIMenuItem(2, fnt, snd, 400, 240, 0.2f, "Options"));
	mainMenu->AddCtrl(new hgeGUIMenuItem(3, fnt, snd, 400, 280, 0.3f, "Exit"));

	mainMenu->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	mainMenu->Enter();
}

SIGNAL Menu::Think()
{
	float delta=hge->Timer_GetDelta();
	int id=mainMenu->Update(delta);

	if(id==1)
		return SIGNAL(SIGNAL_CHANGEINSTANCE, 1);

	return SIGNAL(SIGNAL_TERMINATE, false);
}

void Menu::Render()
{
	mainMenu->Render();
}

Menu::~Menu()
{
	delete mainMenu;
	delete fnt;
	hge->Effect_Free(snd);
	hge->Release();
}