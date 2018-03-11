#include "collisions.h"

using Collisions::CollisionMap;

bool **CollisionMap::collisionMatrix;

bool CollisionMap::CheckCollision(hgeRect *collisionBox)
{
    for(int x=(int)collisionBox->x1; x<collisionBox->x2; x++)
        for(int y=(int)collisionBox->y1; y<collisionBox->y2; y++)
        {
            if(collisionMatrix[x][y]==true)
            {
                return false;
            }
        }
    return true;
}

bool CollisionMap::CheckCollision(circunference *collisionCircunference)
{
	float radius=collisionCircunference->GetRadius();
	float xCenter=collisionCircunference->GetCenter().x;
	float yCenter=collisionCircunference->GetCenter().y;
	for(int x=(int)(xCenter-radius); x<(int)(xCenter+radius); x++)
        for(int y=(int)(yCenter-radius); y<(yCenter+radius); y++)
        {
			if(collisionMatrix[x][y]==true && collisionCircunference->TestPoint(point(x, y))==true)
            {
                return false;
            }
        }
	return true;
}