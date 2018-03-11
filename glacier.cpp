#include "targetMap.h"

using Maps::Glacier;
using Maps::TargetMap;
using Collisions::CollisionMap;

void Glacier::Think(float delta)
{
}

void Glacier::Render()
{
    mapSprite->Render(0, 0);
}
