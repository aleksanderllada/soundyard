#pragma once

#ifndef TARGETMAP_H_INCLUDED
#define TARGETMAP_H_INCLUDED

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgecolor.h"
#include "hgedistort.h"
#include "collisions.h"
#include "math.h"
#include <string>
#include "musicmanager.h"

namespace Maps
{

    using std::string;

    //Base class will do everything that's necessary for loading the map.
    class TargetMap
    {
    protected:
        string              MapName;
        HTEXTURE       collisionTexture;
        HTEXTURE       mapTexture;
        hgeSprite        *mapSprite;
        bool **collisionMatrix;
        int textureSize;

    private:
        void Analyze();

    public:
        virtual ~TargetMap(){}
        virtual void Init();
        virtual bool **GetMatrix() {return collisionMatrix;}

        //From here must be deffined on the derived class, since each map has it's own effects to render.
        virtual void Think(float delta) {}
        virtual void Render() {}
    };

    class Inferno : public TargetMap
    {
    private:
        HTEXTURE              lakeTexture;
        static float            timeElapsed;
        hgeDistortionMesh   *infernoLake;
    public:
        Inferno()
        {
            MapName="Inferno";
            TargetMap::Init();
            Init();
        }
        void Init();
        void Think(float delta);
        void Render();
    };

	class Glacier : public TargetMap
    {
    public:
        Glacier()
        {
            MapName="Glacier";
            TargetMap::Init();
            Init();
        }
		void Init() {}
        void Think(float delta);
        void Render();
    };

}

#endif // TARGETMAP_H_INCLUDED
