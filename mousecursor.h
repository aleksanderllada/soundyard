#pragma once

#ifndef MOUSECURSOR_H_INCLUDED
#define MOUSECURSOR_H_INCLUDED

#include "hge.h"
#include "hgesprite.h"
#include "inputmanager.h"
#include "util.h"

//Global class
class MouseCursor
{
private:
    static float cursorPositionX;
    static float cursorPositionY;
	static HTEXTURE cursorTexture;
    static hgeSprite *cursorSprite;

public:
    MouseCursor(float xPos=0, float yPos=0);

    ~MouseCursor()
    {
        delete cursorSprite;
    }

public:
    static inline void SetPosition(float x, float y) //Must include screen displacement.
    {
        cursorPositionX=x;
        cursorPositionY=y;
    }
    static inline void SetSprite(hgeSprite *sprite)
    {
        cursorSprite=sprite;
    }
    static inline void GetMousePosition(float *x, float *y)
    {
        *x=cursorPositionX;
        *y=cursorPositionY;
    }
    void Render();
    void Think();
};

#endif // MOUSECURSOR_H_INCLUDED
