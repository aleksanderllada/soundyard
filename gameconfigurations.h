#pragma once

#ifndef GAMECONFIGURATIONS_H_INCLUDED
#define GAMECONFIGURATIONS_H_INCLUDED

struct GameConfiguration
{
public:
    static int screenWidth;
    static int screenHeight;
    static int fpsRate;
    static bool zBuffer;
    static bool useSound;
    static bool showSplash;
	static float displacementX;
	static float displacementY;

public:
    static inline void Init()
    {
        screenWidth=1340;
        screenHeight=768;
        fpsRate=200;
        zBuffer=false;
        useSound=true;
        showSplash=true;
		displacementX=0;
		displacementY=0;
    }
};

#endif // GAMECONFIGURATIONS_H_INCLUDED
