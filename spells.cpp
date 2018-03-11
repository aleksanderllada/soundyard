#include "spells.h"

using namespace GeneralSpells;

Spells::Spells(int *_currentEnergy, int maxEnergy)
{
	hge=hgeCreate(HGE_VERSION);

	particleTexture=hge->Texture_Load("Spells/Particles/Particle.png");
	particleSprite=new hgeSprite(particleTexture, 0, 0, 16, 16);
	//particleSprite->SetBlendMode(BLEND_DARKEN | BLEND_ALPHAADD | BLEND_ZWRITE);
	particleSprite->SetHotSpot(8, 8);

	frontTarget=hge->Target_Create(60, 110, false);
	hge->Target_GetTexture(frontTarget, frontTargetTexture);
	frontTargetSprite=new hgeSprite(frontTargetTexture, 0, 0, 60, 110);
	frontTargetSprite->SetHotSpot(30, 55);
	frontTargetSprite->SetBlendMode(BLEND_DEFAULT_Z);

	backTarget=hge->Target_Create(60, 110, false);
	hge->Target_GetTexture(backTarget, backTargetTexture);
	backTargetSprite=new hgeSprite(backTargetTexture, 0, 0, 60, 110);
	backTargetSprite->SetHotSpot(30, 55);
	backTargetSprite->SetBlendMode(BLEND_DEFAULT_Z);
	
	currentEnergy=_currentEnergy;

	particles=new Particle[maxEnergy];

	srand(time(NULL));

	short int multipler=1;

	for(int counter=0; counter<maxEnergy; counter++)
	{
		particles[counter].position.x=rand() % 50 + 10;
		particles[counter].position.y=rand() % 100 + 10;
		particles[counter].xMultipler=multipler;
		particles[counter].yMultipler=multipler;
		multipler*=-1;
	}

	xDisplacement=10; //Pixels per second
	yDisplacement=10;
}

void Spells::MakeTargets()
{
	hge->Gfx_BeginScene(frontTarget);

	for(int counter=0; counter<*currentEnergy; counter++)
	{
		if(particles[counter].xMultipler>0)
		{
			particleSprite->Render(particles[counter].position.x, particles[counter].position.y);
		}
	}

	hge->Gfx_Clear(0);
	hge->Gfx_EndScene();

	hge->Gfx_BeginScene(backTarget);

	for(int counter=0; counter<*currentEnergy; counter++)
	{
		if(particles[counter].xMultipler<0)
		{
			particleSprite->Render(particles[counter].position.x, particles[counter].position.y);
		}
	}

	hge->Gfx_Clear(0);
	hge->Gfx_EndScene();
}

void Spells::Render(float z, point coordinate)
{
	frontTargetSprite->SetZ(z-0.0001);
	backTargetSprite->SetZ(z+0.0001);
	frontTargetSprite->Render(coordinate.x, coordinate.y);
	backTargetSprite->Render(coordinate.x, coordinate.y);
}

void Spells::Think()
{
	xDisplacement=MusicManager::GetMusicSpeed()*3;
	yDisplacement=MusicManager::GetMusicSpeed()*3;

	float delta=hge->Timer_GetDelta();
	for(int counter=0; counter<*currentEnergy; counter++)
	{
		particles[counter].position.x+=(xDisplacement*particles[counter].xMultipler*delta);
		particles[counter].position.y+=(yDisplacement*particles[counter].yMultipler*delta);

		if(particles[counter].position.x>50)
		{
			particles[counter].xMultipler*=-1;
			particles[counter].position.x=50;
		}
		if(particles[counter].position.x<10)
		{
			particles[counter].xMultipler*=-1;
			particles[counter].position.x=10;
		}
		if(particles[counter].position.y>100)
		{
			particles[counter].yMultipler*=-1;
			particles[counter].position.y=100;
		}
		if(particles[counter].position.y<10)
		{
			particles[counter].yMultipler*=-1;
			particles[counter].position.y=10;
		}
	}
}