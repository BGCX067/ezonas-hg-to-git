#include "stdafx.h"
class Game
{
public:
	static Game * GetSingleton();
	//Sprite * mySprite;

	HRESULT InitD3D (HWND hWnd );
	VOID Render();
	//INT WINAPI wWinMain (HINSTANCE hInst, HINSTANCE, LPSTR, INT, WNDPROC);
	VOID Cleanup();
	LPDIRECT3D9 getd3d() { return g_pD3D; };
	LPDIRECT3DDEVICE9 getdevice() { return g_pd3dDevice; }
	void SetSprite(Sprite * _sprite) { sprite = _sprite; }
	void Go();
protected:
	Game();
	~Game();
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	LPDIRECT3D9 g_pD3D;
	Sprite * sprite;
	WNDCLASSEX wc;
	HWND hWnd;
};