#include "targetMap.h"
#include "collisions.h"

using Maps::TargetMap;
using Collisions::CollisionMap;

//Maps prototype
void TargetMap::Analyze()
{
    //Get pointer
    HGE *hge;
    hge=hgeCreate(HGE_VERSION);

    //Load texture
    string loadMappedName;
    loadMappedName="Maps/Mapped_";
    loadMappedName+=MapName;
    loadMappedName+=".png";
    collisionTexture=hge->Texture_Load(loadMappedName.data());
    textureSize=hge->Texture_GetWidth(collisionTexture);

    //Lock texture
    DWORD *MappingResult;
    MappingResult=hge->Texture_Lock(collisionTexture);

    //Create matrix with dynamic allocation
    collisionMatrix=new bool*[textureSize-2];

        for(int x=0; x<textureSize; x++)
           collisionMatrix[x] = new bool[textureSize-2];

    //Analyze texture and fill matrix
    DWORD color;
    for(int x=1; x<(textureSize-1); x++)
        for(int y=1; y<(textureSize-1); y++)
        {
            color=MappingResult[y*textureSize+x];
			if(color==0xFFFFFFFF)
                collisionMatrix[x][y]=true;
            else
                collisionMatrix[x][y]=false;
        }

    //Unlock texture
    hge->Texture_Unlock(collisionTexture);

    //Free everything
    hge->Texture_Free(collisionTexture);
    hge->Release();
}

void TargetMap::Init()
{
    //Create collision matrix
    Analyze();

    //Get pointer
    HGE *hge;
    hge=hgeCreate(HGE_VERSION);

    //Load texture
    string loadMapName;
    loadMapName="Maps/";
    loadMapName+=MapName;
    loadMapName+=".png";
    mapTexture=hge->Texture_Load(loadMapName.data());

    //Create sprite
    mapSprite=new hgeSprite(mapTexture, 1, 1, (float)textureSize-1, (float)textureSize-1);
    mapSprite->SetHotSpot(0, 0);
	mapSprite->SetZ(1.0f);

    //Free pointer
    hge->Release();
}
