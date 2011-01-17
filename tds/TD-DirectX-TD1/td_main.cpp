#include "stdafx.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE a, LPSTR b, INT c)
{
	Game * game = Game :: GetSingleton();
	Sprite * sprite = new Sprite(game -> getdevice());
	game -> SetSprite(sprite);
	game -> Go();
	//system("PAUSE");
}