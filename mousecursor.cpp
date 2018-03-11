#include "mousecursor.h"

float MouseCursor::cursorPositionX;
float MouseCursor::cursorPositionY;
HTEXTURE MouseCursor::cursorTexture;
hgeSprite *MouseCursor::cursorSprite;

MouseCursor::MouseCursor(float xPos, float yPos)
{
	HGE *hge=hgeCreate(HGE_VERSION);
    cursorPositionX=xPos;
    cursorPositionY=yPos;
	cursorTexture=hge->Texture_Load("Ui/Cursor.png");
    cursorSprite=new hgeSprite(cursorTexture, 0, 0, 20, 20);
    cursorSprite->SetHotSpot(0, 0);
	cursorSprite->SetBlendMode(BLEND_DEFAULT_Z);
	cursorSprite->SetZ(0.0f);
	hge->Release();
}

void MouseCursor::Render()
{
    cursorSprite->Render(cursorPositionX, cursorPositionY);
}

void MouseCursor::Think()
{
	SetPosition(InputManager::GetMousePos().x, InputManager::GetMousePos().y);
}