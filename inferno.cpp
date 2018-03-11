#include "targetMap.h"

using Maps::Inferno;
using Maps::TargetMap;
using Collisions::CollisionMap;

float Inferno::timeElapsed=0.0f;

void Inferno::Init()
{
    //Then set up this map
    //Create pointer
    HGE *hge;
    hge=hgeCreate(HGE_VERSION);

    //Create texture
    lakeTexture=hge->Texture_Load("Maps/Inferno_Lake.png");

    //Create distortion mash
    infernoLake=new hgeDistortionMesh(8, 8);
    infernoLake->SetTexture(lakeTexture);
    infernoLake->SetTextureRect(0, 0, 300, 240);
    infernoLake->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_ZWRITE);
    infernoLake->Clear(0xFF000000);
}

void Inferno::Think(float delta)
{
    timeElapsed+=delta/3;
    float speed=MusicManager::GetMusicSpeed();
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
			infernoLake->SetZ(j, i, 1.0);
			infernoLake->SetDisplacement(j,i,cosf(timeElapsed*10+(i+j)/2)*speed,sinf(timeElapsed*10+(i+j)/2)*speed,HGEDISP_NODE);
        }
}

void Inferno::Render()
{
    infernoLake->Render(410, 230);
    mapSprite->Render(0, 0);
}
