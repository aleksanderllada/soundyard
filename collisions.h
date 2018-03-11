#pragma once

#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "hgerect.h"
#include "util.h"

namespace Collisions
{

    class CollisionMap
    {
    private:
        static bool **collisionMatrix;
    public:
        CollisionMap(bool **matrix){ collisionMatrix=matrix; }
        static bool CheckCollision(hgeRect *collisionBox);
		static bool CheckCollision(circunference *collisionCircunference);
    };


}

#endif // COLLISIONS_H_INCLUDED
