#include "hud.h"

using namespace HUD;

HeadsUpDisplay::HeadsUpDisplay()
{
	hge=hgeCreate(HGE_VERSION);
	hudTarget=hge->Target_Create(246, 56, false);
	hge->Target_GetTexture(hudTarget, targetTexture);
	targetSprite=new hgeSprite(targetTexture, 0, 0, 246, 56);
	targetSprite->SetBlendMode(BLEND_DEFAULT_Z);
	targetSprite->SetZ(0.1f);

	hudTexture=hge->Texture_Load("HUD/HUD.png");

	hudSprite=new hgeSprite(hudTexture, 1, 1, 247, 57);
	hudHP=new hgeSprite(hudTexture, 1, 62, 41, 23);
	hudEnergy=new hgeSprite(hudTexture, 50, 70, 73, 15);

	energyTexture=hge->Texture_Load("HUD/EnergyBars/Energy.png");
	energyAnimation=new hgeAnimation(energyTexture, 10, 20, 0, 0, 250, 23);
	energyAnimation->SetBlendMode(BLEND_DARKEN | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	energyAnimation->Play();
}

void HeadsUpDisplay::Think(int _currentElement)
{
	float delta=hge->Timer_GetDelta();
	energyAnimation->Update(delta);
}

void HeadsUpDisplay::MakeTargets(float healthPercent)
{
	hge->Gfx_BeginScene(hudTarget);
	hge->Gfx_Clear(0);

	hudSprite->Render(0,0);
	
	hgeSprite *hpBar=new hgeSprite(0, 0, 0, 250*healthPercent, 33);
	hpBar->SetColor(ARGB(255, 255, 0, 0));
	hpBar->SetBlendMode(BLEND_DARKEN | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	hpBar->Render(0, 0);

	energyAnimation->Render(0, 33);

	delete hpBar;

	hge->Gfx_EndScene();
}

void HeadsUpDisplay::Render(float displacementX, float displacementY)
{
	targetSprite->Render(-displacementX+10, GameConfiguration::screenHeight-56-displacementY-10);
}

HeadsUpDisplay::~HeadsUpDisplay()
{
	hge->Release();
}